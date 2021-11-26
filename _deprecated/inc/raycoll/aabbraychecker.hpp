#ifndef GLEWY_DYNRAYBOX_HPP
#define GLEWY_DYNRAYBOX_HPP

#include<substd/vec.hpp>
#include<Glewy/Core/typedef.hpp>

#include<Glewy/Standard/RayCollisions/raychecker.hpp>

namespace ss{
    class Transform;
}

namespace gly{

class RayCollisionGroup;

class AABBRayChecker : public RayChecker {
public:
    ss::Transform* transform;

    gly_int vertical_resolution = 5;
    gly_int horizontal_resolution = 5;

    gly_float AllowedHorizontalMove(const gly_float& attempt, RayCollisionGroup* group) const override;
    gly_float AllowedVerticalMove(const gly_float& attempt, RayCollisionGroup* group) const override;
    ss::vec2<gly_float> AllowedMove(const ss::vec2<gly_float>& attempt, RayCollisionGroup* group) const override;
};

}

#endif