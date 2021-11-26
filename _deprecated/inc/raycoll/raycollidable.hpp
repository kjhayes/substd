#ifndef GLEWY_RAYCOLLIDABLE_HPP
#define GLEWY_RAYCOLLIDABLE_HPP

#include<substd/ray.hpp>
#include<Glewy/Core/typedef.hpp>    

namespace gly{

class RayCollidable{
protected:
    typedef gly_float RCType;
    typedef ss::Ray<RCType> RCRay;
    typedef gly_float RCReturnType;
public:
    virtual RCReturnType Collide(const RCRay& ray) const;
    virtual RCReturnType HorizontalCollide(const RCRay& ray) const;
    virtual RCReturnType VerticalCollide(const RCRay& ray) const;
};

}

#endif