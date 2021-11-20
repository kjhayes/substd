/**
 * @file
 * @author Kevin Hayes
 * @include array iterator algorithm functional type_traits iostream
*/

#ifndef SUBSTD_VEC_HPP
#define SUBSTD_VEC_HPP

#include<array>
#include<iterator>
#include<algorithm>
#include<functional>
#include<type_traits>
#include<iostream>

namespace ss
{

/**
 * @class vec
 * 
 * @tparam T Type of the vector, if it is a fundamental type, it must be arithmetic 
 * @tparam dim The size of the vector. Must be greater than zero.
*/
template<typename T, std::size_t dim=1> 
class vec : public std::array<T, dim> {
    static_assert(!((std::is_fundamental_v<T>)^(std::is_arithmetic_v<T>)), "Fundamental types passed as the template parameter of ss::vec<> are required to be arithmetic");
    static_assert(dim > 0, "ss::vec<> requires at least l dimension");

protected:
    using base = std::array<T, dim>;
    using V = vec<T, dim>;

    template<typename OT, size_t Odim>
    V GenerateBinary(const vec<OT, Odim>& other, const std::function<T(const T&, const OT&)>& f) const {
        V ret;
        if constexpr(dim >= Odim){
            std::transform(other.begin(), other.end(), base::begin(), ret.begin(), f);
        }
        else {
            std::transform(base::begin(), base::end(), other.begin(), ret.begin(), f);
        }
        return ret;
    }
    
    template<typename S>
    V GenerateUnary(const std::function<T(const T&)>& f) const {
        V ret;
        std::transform(base::begin(), base::end(), ret.begin(), f);
        return ret;
    }
    
    template<typename OT, size_t Odim>
    void ReflexiveBinary(const vec<OT, Odim>& other, const std::function<void(T&, const OT&)>& f){
        if constexpr(dim >= Odim){
            std::transform(other.begin(), other.end(), base::begin(), f);
        }
        else {
            std::transform(base::begin(), base::end(), other.begin(), f);
        }
    }
    void ReflexiveUnary(const std::function<void(T&)>& f){
        std::transform(base::begin(), base::end(), base::begin(), f);
    }

public:
    /**
     * @brief Default Constructor
    */
    vec(){}
    /**
     * @brief Fill Constructor
    */
    vec(const T& t){
        std::fill(base::begin(), base::end(), t);
    }
    /**
     * @brief Range Copy Constructor
    */
    template<typename OT, size_t Odim, template<typename ROT, size_t ROdim> typename R>
    vec(const R<OT, Odim>& other){
        if constexpr(dim >= Odim) {
            std::copy(other.begin(), other.end(), base::begin());
        }
        else {
            std::copy_n(other.begin(), dim, base::begin());
        }    
    }
    /**
     * @brief Initializer List Constructor
    */
    template<typename OT>
    constexpr vec(std::initializer_list<OT> i){
        if (dim >= i.size()) {
            std::copy(i.begin(), i.end(), base::begin());
        }
        else {
            std::copy_n(i.begin(), dim, base::begin());
        }
    }

    /**
     * @brief Range Copy Assignment Operator
    */
    template<typename OT, size_t Odim, template<typename ROT, size_t ROdim> typename R>
    void operator=(const R<OT, Odim>& other){
        if constexpr(dim >= Odim) {
            std::copy(other.begin(), other.end(), base::begin());
        }
        else {
            std::copy_n(other.begin(), dim, base::begin());
        }    
    }

    //Generated

    template<typename OT, size_t Odim>
    V Sum(const vec<OT, Odim>& other) const {
        return GenerateBinary<OT, Odim>(other, [](const T& a, const OT& b)->T{return a+b;});
    }
    template<typename OT, size_t Odim>
    V Dif(const vec<OT, Odim>& other) const {
        return GenerateBinary(other, [](const T& a, const OT& b)->T{return a-b;});
    }

    template<typename S>
    V Prod(const S& s) const {
        return GenerateUnary([s](const T& a)->T{return a*s;});
    }
    template<typename S>
    V Quot(const S& s) const {
        return GenerateUnary([s](const T& a)->T{return a/s;});
    }
    template<typename S>
    V LeftProd(const S& s) const {
        return GenerateUnary([s](const T& a)->T{return s*a;});
    }
    template<typename S>
    V LeftQuot(const S& s) const {
        return GenerateUnary([s](const T& a)->T{return s/a;});
    }
    
    //Reflexive

    template<typename OT, size_t Odim>
    void Add(const vec<OT, Odim>& other) {
        ReflexiveBinary(other, [](T& a, const OT& b)->void{a += b;});
    }
    template<typename OT, size_t Odim>
    void Sub(const vec<OT, Odim>& other) {
        ReflexiveBinary(other, [](T& a, const OT& b)->void{a -= b;});
    }

    template<typename S>
    void Mul(const S& s){
        ReflexiveUnary([s](T& a)->void{a *= s;});
    }
    template<typename S>
    void Div(const S& s){
        ReflexiveUnary([s](T& a)->void{a /= s;});
    }
    
    template<typename S>
    void LeftMul(const S& s){
        ReflexiveUnary([s](T& a)->void{a = s*a;});
    }
    template<typename S>
    void LeftDiv(const S& s){
        ReflexiveUnary([s](T& a)->void{a = s/a;});
    }

    template<typename OT, size_t Odim>
    auto Dot(const vec<OT, Odim>& other) const {
        auto sum = T(0)*OT(0);
        if constexpr (dim >= Odim){
            for(int i = 0; i < Odim; i++){
                sum += (base::at(i) * other.at(i));
            }
        }
        else{
            for(int i = 0; i < dim; i++){
                sum += (base::at(i) * other.at(i));
            }
        }
        return sum;
    }
    
    auto MagnitudeSqr() const {
        auto sum = T(0) * T(0);
        std::for_each(base::begin(), base::end(), [sum](const T& t)->void{sum += (t*t);})
        return sum;
    }

    template<typename OT = T>
    auto Magnitude() const {
        return Sqrt<OT>(MagnitudeSqr());
    }

    template<typename OT, size_t Odim>
    V operator+(const vec<OT, Odim>& other) const {return Sum(other);}  
    template<typename OT, size_t Odim>
    void operator+=(const vec<OT, Odim>& other) {Add(other);}
    
    template<typename OT, size_t Odim>
    V operator-(const vec<OT, Odim>& other) const {return Dif(other);}
    template<typename OT, size_t Odim>
    void operator-=(const vec<OT, Odim>& other) {Sub(other);}
    
    template<typename S>
    V operator*(const S& scalar) const {return Prod(scalar);}
    template<typename S>
    friend S operator*(const S& scalar,const V& v){return v.LeftProd(scalar);}
    template<typename S>
    void operator*=(const S& scalar) {Mult(scalar);}
    
    template<typename S>
    V operator/(const S& scalar) const {return Quot(scalar);}
    template<typename S>
    friend S operator/(const S& scalar,const V& v){return v.LeftQuot(scalar);}
    template<typename S>
    void operator/=(const S& scalar) {Div(scalar);}

    friend std::ostream& operator<<(std::ostream& o, const V& v)
    {
        o<<"("<<v.front();
        for(auto iter = v.begin()+1; iter!=v.end(); iter++){
            o<<", "<<(*iter);
        }
        o<<")";
        return o;
    }

    template<size_t u=0>
    static constexpr V Unit(){
        static_assert(u<dim);
        V ret(0);
        ret.at(u) = 1;
        return ret;
    }
};

template<typename T>
using vec2 = vec<T,2>;
template<typename T>
using vec3 = vec<T,3>;
template<typename T>
using vec4 = vec<T,4>;

using vec2f = vec2<float>;
using vec3f = vec3<float>;
using vec4f = vec4<float>;

using vec2d = vec2<double>;
using vec3d = vec3<double>;
using vec4d = vec4<double>;

using vec2i = vec2<int>;
using vec3i = vec3<int>;
using vec4i = vec4<int>;

}
#endif // SUBSTD_VEC_HPP