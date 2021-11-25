#ifndef SUBSTD_MATH_HPP
#define SUBSTD_MATH_HPP

#include<type_traits>
#include<iterator>
#include<cmath>

#include<substd/constants.hpp>

namespace ss{
    /**
     * @fn Max
     * @return T The maximum of the two parameters
     */
    template<typename T> constexpr T Max(const T& a, const T& b){
        return (a>b) ? a : b;
    }
    /**
     * @fn Min
     * @return T The maximum of the two parameters
     */
    template<typename T> constexpr T Min(const T& a, const T& b){
        return (a<b) ? a : b;
    }
    /**
     * @fn Pow
     * @param base The base of the exponent
     * @param pow The power to raise the base to
     */
    template<typename T> constexpr T Pow(const T& base, const T& pow){
        return (T)std::pow(base, pow);
    }

    /**
     * @fn Sqrt 
     */
    template<typename T> constexpr T Sqrt(const T& base){
        return (T)std::sqrt((double)base);
    }

    /**
     * @fn Floor
     * @return T The floored value of f
     */
    template<typename T> constexpr T Floor(const T& f){
        return (T)std::floor(f);
    }
    /**
     * @fn Abs
     * @return T The absolute value of a
     */
    template<typename T> constexpr T Abs(const T& a){
        return (T)std::abs(a);
    }
    /**
     * @fn Nearest
     * @return T the value of a or b, whichever is closest to p
     * @remark If the two values are equal, which value is returned is undefined.
     */
    template<class T> constexpr T Nearest(const T& a, const T& b, const T& p){
        return Min<T>(Abs<T>(to-a),Abs<T>(to-b));
    }

    //Trigonometic Functions

    inline constexpr trig_t DegreeToRad(const trig_t& deg){
        return deg * PI_DIV_180;
    }
    inline constexpr trig_t RadToDegree(const trig_t& rad){
        return rad * _180_DIV_PI;
    }
    /**
     * @fn Sin
     * @param theta In Radians
     */
    inline constexpr trig_t Sin(const trig_t& theta) {
        return (trig_t)std::sin((double)theta);;
    }
    /**
     * @fn Cos
     * @param theta In Radians
     */
    inline constexpr trig_t Cos(const trig_t& theta) {
        return (trig_t)std::cos((double)theta);
    }

    //Pairing Functions
    
    template<class T> T MapIntToPositive(const T& i){
        static_assert(std::is_integral_v<T>(), "MapIntToPositive() requires an integral type!");
        if(i>=0){return i<<1;}
        return (-2*i) + 1;
    }
    template<class T> T CantorPair(const T& x, const T& y){
        static_assert(std::is_integral_v<T>(), "CantorPair() requires an integral type!");
        return (
            ((T)(((x+y)*(x+y+1))*0.5f))+y
        );
    }
    template<class T> T SignedCantorPair(const T& x, const T& y){
        static_assert(std::is_integral_v<T>(), "SignedCantorPair() requires an integral type!");
        return CantorPair(MapIntToPositive<T>(x), MapIntToPositive<T>(y));
    }
    template<class T> T SzudzikPair(const T& x, const T& y){
        static_assert(std::is_integral_v<T>(), "SzudzikPair() requires an integral type!");
        if(x>=y){return (x*x)+x+y;}
        return (y*y)+x;
    }
    template<class T> T SignedSzudzikPair(const T& x, const T& y){
        static_assert(std::is_integral_v<T>(), "SignedSzudzikPair() requires an integral type!");
        return SzudzikPair(MapIntToPositive<T>(x), MapIntToPositive<T>(y));
    }
}

#endif//SUBSTD_MATH_HPP