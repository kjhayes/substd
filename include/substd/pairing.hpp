#ifndef SUBSTD_PAIRING_HPP
#define SUBSTD_PAIRING_HPP

namespace ss{

template<class T> T MapIntToPositive(const T& i){
    if(i>=0){return i<<1;}
    return (-2*i) + 1;
}

template<class T> T CantorPair(const T& x, const T& y){
    return (
        ((T)(((x+y)*(x+y+1))*0.5f))+y
    );
}
template<class T> T SignedCantorPair(const T& x, const T& y){
    return CantorPair(MapIntToPositive<T>(x), MapIntToPositive<T>(y));
}
template<class T> T SzudzikPair(const T& x, const T& y){
    if(x>=y){return (x*x)+x+y;}
    return (y*y)+x;
}
template<class T> T SignedSzudzikPair(const T& x, const T& y){
    return SzudzikPair(MapIntToPositive<T>(x), MapIntToPositive<T>(y));
}

}

#endif