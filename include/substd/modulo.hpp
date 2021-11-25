#ifndef SUBSTD_MODULO_HPP
#define SUBSTD_MODULO_HPP

#include<substd/constants.hpp>
#include<substd/interfaces.hpp>
#include<cmath>

namespace ss{

///@class modular
///@brief base class for IContrainable classes which have a Modulus
template<class self, typename T>
class modular : public IConstrainable<T> {
public:
    static constexpr T Modulus();
    T EvalValue(const T& t) override {return fmod(t, Modulus());}
};

///@class modulo_pi
template<class T>
class modulo_pi : public modular<modulo_pi<T>, T> {
public:
    modulo_pi(const T& t):IConstrainable<T>(t){}
    constexpr T Modulus() {
        return (T)SS_PI;
    }
    void operator=(const T& eq){return IConstrainable<T>::operator=(eq);}
};
///@class modulo_tau
///@remark Especially useful for storing rotations.
template<class T>
class modulo_tau : public modular<modulo_tau<T>, T> {
public:
    modulo_tau(const T& t):IConstrainable<T>(t){}
    constexpr T Modulus() {
        return (T)SS_TAU;
    }
    void operator=(const T& eq){return IConstrainable<T>::operator=(eq);}
};

}

#endif //GLEWY_MODULO_HPP