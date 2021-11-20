#ifndef SUBSTD_RECT_HPP
#define SUBSTD_RECT_HPP

#include<substd/vec.hpp>
#include<substd/corner.hpp>

namespace ss{

const vec2<ss_float> UnitCorner[4] = {
    {-0.5f,-0.5f},
    {0.5f,-0.5f},
    {-0.5f,0.5f},
    {0.5f,0.5f}
};

template<class T>
struct Rect{
public:
    vec2<T> center;
    vec2<T> dimensions;

    Rect():center(0,0),dimensions(1.0f,1.0f){}
    Rect(const vec2<T>& cen):center(cen),dimensions(1.0f,1.0f){}
    Rect(const vec2<T>& cen, const vec2<T>& dim):center(cen),dimensions(dim){}

    vec2<T> GetCorner(const CORNER& corner) const {
        return center + vec2<T>(UnitCorner[corner].x*dimensions.x, UnitCorner[corner].y*dimensions.y); 
    }
};

}

#endif