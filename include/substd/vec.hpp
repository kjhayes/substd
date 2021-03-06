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

#include "substd/constants.hpp"

namespace ss
{

/**
 * @class vec
 * 
 * @tparam T Type of the vector, if it is a fundamental type, it must be arithmetic 
 * @tparam dim The size of the vector. Must be greater than zero.
*/
template<typename T, size_t dim=1> 
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
    V GenerateUnary(const std::function<T(const T&)>& f) const {
        V ret;
        std::transform(base::begin(), base::end(), ret.begin(), f);
        return ret;
    }
    template<typename S>
    vec<S,dim> GenerateLeftUnary(const std::function<S(const T&)>& f) const {
        vec<S,dim> ret;
        std::transform(base::begin(), base::end(), ret.begin(), f);
        return ret;
    }

    template<typename OT, size_t Odim>
    void ReflexiveBinary(const vec<OT, Odim>& other, const std::function<void(T&, const OT&)>& f){
        if constexpr(dim >= Odim){
            for(int i = 0; i < Odim; i++){
                f(base::at(i), other.at(i));
            }
        }
        else {
            for(int i = 0; i < dim; i++){
                f(base::at(i), other.at(i));
            }
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
     * @brief Range Copy Constructor, Copies As Many Elements As Possible From The Range, Any Extra Are Filled.
     * @param fill Value To Fill The Remaining Elements With
    */
    template<typename OT, size_t Odim, template<typename ROT, size_t ROdim> typename R>
    vec(const R<OT, Odim>& other, const T& fill = 0){
        if constexpr(dim >= Odim) {
            std::copy(other.begin(), other.end(), base::begin());
            std::fill(base::begin()+Odim, base::end(), fill);
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

    ///@fn Sum
    template<typename OT, size_t Odim>
    V Sum(const vec<OT, Odim>& other) const {
        return GenerateBinary<OT, Odim>(other, [](const T& a, const OT& b)->T{return (T)(a+b);});
    }
    ///@fn Dif
    template<typename OT, size_t Odim>
    V Dif(const vec<OT, Odim>& other) const {
        return GenerateBinary(other, [](const T& a, const OT& b)->T{return (T)(a-b);});
    }
    ///@fn Prod
    template<typename S>
    V Prod(const S& s) const {
        return GenerateUnary([s](const T& a)->T{return (T)(a*s);});
    }
    ///@fn Quot
    template<typename S>
    V Quot(const S& s) const {
        return GenerateUnary([s](const T& a)->T{return (T)(a/s);});
    }
    ///@fn LeftProd
    template<typename S>
    vec<S, dim> LeftProd(const S& s) const {
        return GenerateLeftUnary<S>([s](const T& a)->S{return (S)(s*a);});
    }
    ///@fn LeftQuot
    template<typename S>
    vec<S, dim> LeftQuot(const S& s) const {
        return GenerateLeftUnary<S>([s](const T& a)->S{return (S)(s/a);});
    }
    
    ///@fn Add
    template<typename OT, size_t Odim>
    void Add(const vec<OT, Odim>& other) {
        ReflexiveBinary<OT, Odim>(other, [](T& a, const OT& b)->void{a += b;});
    }
    ///@fn Sub
    template<typename OT, size_t Odim>
    void Sub(const vec<OT, Odim>& other) {
        ReflexiveBinary(other, [](T& a, const OT& b)->void{a -= b;});
    }
    ///@fn Mul
    template<typename S>
    void Mul(const S& s){
        ReflexiveUnary([s](T& a)->void{a *= s;});
    }
    ///@fn Div
    template<typename S>
    void Div(const S& s){
        ReflexiveUnary([s](T& a)->void{a /= s;});
    }
    ///@fn LeftMul
    template<typename S>
    void LeftMul(const S& s){
        ReflexiveUnary([s](T& a)->void{a = s*a;});
    }
    ///@fn LeftDiv
    template<typename S>
    void LeftDiv(const S& s){
        ReflexiveUnary([s](T& a)->void{a = s/a;});
    }

    ///@fn Dot
    template<typename OT, size_t Odim>
    T Dot(const vec<OT, Odim>& other) const {
        T sum = 0;
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
    
    ///@fn MagnitudeSqr
    auto MagnitudeSqr() const {
        auto sum = T(0) * T(0);
        std::for_each(base::begin(), base::end(), [sum](const T& t)->void{sum += (t*t);});
        return sum;
    }

    ///@fn Magnitude
    template<typename OT = ss_trig>
    auto Magnitude() const {
        return Sqrt<OT>(MagnitudeSqr());
    }

    ///@fn Normalized
    template<typename OT = ss_trig>
    vec<OT, dim> Normalized() const {
        return LeftProd<OT>(1/Magnitude());
    }

    ///@fn Homogenized
    vec<T,dim+1> Homogenized(const T& fill = 1) const {
        return vec<T,dim+1>(*this, fill);
    }

    //Operators

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
    //template<typename S>
    //friend S operator*(const S& scalar,const V& v){return v.LeftProd(scalar);}
    template<typename S>
    void operator*=(const S& scalar) {Mult(scalar);}
    
    template<typename S>
    V operator/(const S& scalar) const {return Quot(scalar);}
    //template<typename S>
    //friend S operator/(const S& scalar,const V& v){return v.LeftQuot(scalar);}
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

//static
    ///@fn Dimension
    static constexpr size_t Dimension() { return dim; }

    ///@fn Unit
    static V Unit(const size_t& u, const T& value = 1){
        V ret(0);
        ret.at(u) = value;
        return ret;
    }
};

//common typedef/using statements
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