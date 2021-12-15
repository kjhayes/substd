#ifndef GLEWY_RAYCOLLISIONGROUP_HPP
#define GLEWY_RAYCOLLISIONGROUP_HPP

#include<Glewy/Standard/RayCollisions/raycollidable.hpp>

#include<list>

namespace gly{

class RayCollisionGroup : public RayCollidable {
protected:
    std::list<RayCollidable*>* colliders;

public:
    RayCollisionGroup();
    ~RayCollisionGroup();

    RCReturnType Collide(const RCRay& ray) const override;
    RCReturnType HorizontalCollide(const RCRay& ray) const override;
    RCReturnType VerticalCollide(const RCRay& ray) const override;

    void AddCollider(RayCollidable*);
    void RemoveCollider(RayCollidable*);
};

}

#endif