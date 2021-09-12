#ifndef SUBSTD_MODULO_HPP
#define SUBSTD_MODULO_HPP

#include<substd/constants.hpp>
#include<substd/imodifiable.hpp>
#include<cmath>

namespace ss{

template<class self, typename T>
class modular {
public:
    static constexpr T Modulus();
};

template<class T>
class modulo_tau : public modular<modulo_tau<T>, T>, public IModifiable<T>{
public:
    modulo_tau(const T& t):IModifiable<T>(t){}
    constexpr T Modulus() {
        return (T)SS_TAU;
    }
    T EvalValue(const T& t) override {return fmod(t, Modulus());}
    inline void operator=(const T& eq){return IModifiable<T>::operator=(eq);}
};

}

#endif //GLEWY_MODULO_HPP