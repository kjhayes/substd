///@file
///@author Kevin Hayes

#ifndef SUBSTD_MATH_HPP
#define SUBSTD_MATH_HPP

#include<vector>
#include<substd/range.hpp>
#include<algorithm>
#include<cmath>

namespace ss{

template<class T> static double Pow(const T& base, const T& pow){
    return std::pow((double)base, (double)pow);
}
template<class T> static double Floor(const T& f){
    return floor(f);        
}
template<class T> static T Abs(const T& num){
    return std::abs(num); 
    /*
    Ok the difference between abs() and std::abs() just lost me a few hours of my life.
        -This is sad.
    */
}
//MinMax Functions

template<class T> static T Max(const T& a, const T& b){
    if(b>a){return b;}
    else{return a;}
}    
template<class T> static T Min(const T& a, const T& b){
    if(b<a){return b;}
    else{return a;}
}

//

//Closest Functions

template<class T> static T Nearest(const T& a, const T& b, const T& to){
    return Min<T>(Abs<T>(to-a),Abs<T>(to-b));
}
template<class T> static T Nearest(const Range<T>& r, const T& to){
    if(to<=r.GetMidpoint()){return r.GetMin();}
    else{return r.GetMax();}
}


//Between Functions

template<class T> static bool InclusiveBetween(T a, T b, const T& is_between){
    if(b<a){std::swap(a,b);}
    return (a<=is_between && is_between<=b);
}
template<class T> static bool InclusiveBetween(const Range<T>& r, const T& is_between){
    return (r.GetMin()<=is_between && is_between<=r.GetMax());
}
template<class T> static bool ExclusiveBetween(T a, T b, const T& is_between){
    if(b<a){std::swap(a,b);}
    return (a<is_between && is_between<b);
}
template<class T> static bool ExclusiveBetween(const Range<T>& r, const T& is_between){
    return (r.GetMin()<is_between && is_between<r.GetMax());
}

//

//Lerp
template<class T> static T Lerp(const T& a, const T& b, const ss_float& f){
    return (b*f) + (a*(1.0f-f));
}
//

}

}
#endif