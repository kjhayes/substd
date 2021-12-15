#include<Glewy/Standard/RayCollisions/raycollidable.hpp>

namespace gly{

RayCollidable::RCReturnType RayCollidable::Collide(const RCRay& ray) const {return ray.GetMagnitude();}
RayCollidable::RCReturnType RayCollidable::HorizontalCollide(const RCRay& ray) const {return Collide(ray);}
RayCollidable::RCReturnType RayCollidable::VerticalCollide(const RCRay& ray) const {return Collide(ray);}

}