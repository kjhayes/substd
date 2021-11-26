#ifndef GLEWY_RCAABB_HPP
#define GLEWY_RCAABB_HPP

#include<Glewy/Standard/RayCollisions/raycollidable.hpp>

#include<Glewy/Scene/attachment.hpp>

namespace gly{

class AABBRayCollider : public Attachment, public RayCollidable {
friend class gly::Entity;
protected:
    AABBRayCollider(Entity* e);
public: 
    RCReturnType Collide(const RCRay& ray) const override;
    RCReturnType HorizontalCollide(const RCRay& ray) const override;
    RCReturnType VerticalCollide(const RCRay& ray) const override;
};

}

#endif