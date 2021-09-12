#ifndef SUBSTD_UTIL_HPP
#define SUBSTD_UTIL_HPP

#include<list>
#include<substd/vec.hpp>

#include<algorithm>

namespace ss
{

std::list<vec2<ss_float>> PointsBetween(const vec2<ss_float>&, const vec2<ss_float>&, const int&);

ss_float DegToRad(const ss_float&);
ss_float RadToDeg(const ss_float&);

template<class T> inline bool ListContains(std::list<T>* list, const T& elem){
    return std::find(list->begin(), list->end(), elem) != list->end();
}

}

#endif