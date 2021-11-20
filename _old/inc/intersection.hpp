#ifndef SUBSTD_INTERSECTION_HPP
#define SUBSTD_INTERSECTION_HPP

#include<substd/vec.hpp>
#include<substd/rect.hpp>
#include<substd/ray.hpp>
#include<substd/math.hpp>
#include<substd/corner.hpp>

namespace ss{


template<class T>
bool InclusiveOverlap(const Range<T>& a, const Range<T>& b){
    return ((a.GetMin() <= b.GetMax()) && (b.GetMin() <= a.GetMax()));
}
template<class T>
bool ExclusiveOverlap(const Range<T>& a, const Range<T>& b){
    return ((a.GetMin() < b.GetMax()) && (b.GetMin() < a.GetMax()));
}

template<class T>
bool Overlap(const Rect<T>& a, const Rect<T>& b){
    vec2<T> ac = a.GetCorner(CORNER_BOTTOM_LEFT);
    vec2<T> bc = b.GetCorner(CORNER_BOTTOM_LEFT);
    if(
        (ac.x < bc.x + b.dimensions.x) &&
        (bc.x < ac.x + a.dimensions.x) &&
        (ac.y < bc.y + b.dimensions.y) &&
        (bc.y < ac.y + a.dimensions.y)
    ){return true;}
    else{return false;}
}

template<class T>
bool Overlap(const Ray<T>& ray, const Rect<T>& rect){
    vec2<T> bl_time = (rect.GetCorner(CORNER_BOTTOM_LEFT) - ray.GetOrigin()); //Distance;
    vec2<T> tr_time = (rect.GetCorner(CORNER_TOP_RIGHT) - ray.GetOrigin()); //Distance;
    vec2<T> inv_dir = 1.0f/ray.GetDirection();
    bl_time.x *= inv_dir.x;
    bl_time.y *= inv_dir.y;
    tr_time.x *= inv_dir.x;
    tr_time.y *= inv_dir.y;
    vec2<T> near;
    vec2<T> far;
    if(bl_time.x < tr_time.x){near.x = bl_time.x;far.x = tr_time.x;}
    else{near.x = tr_time.x; far.x = bl_time.x;}
    if(bl_time.y < tr_time.y){near.y = bl_time.y; far.y = tr_time.y;}
    else{near.y = tr_time.y; far.y = bl_time.y;}
    
    if(near.x > far.y || near.y > far.x){return false;}
    near.x = Math::Max<T>(near.x, near.y);
    far.x = Math::Max<T>(far.x, far.y);
    if(near.x >= 1 || far.x <= 0){return false;}
    return true;
}

template<class T>
T LinearRayHit(const T& origin, const T& dir, const T& wall_pos){
    if(!Math::InclusiveBetween(origin,origin+dir,wall_pos)){return dir;}
    else{return wall_pos-origin;}
}


}

#endif