#ifndef GLEWY_RAYCHECKER_HPP
#define GLEWY_RAYCHECKER_HPP

#include<substd/vec.hpp>

namespace ss{

class RayCollisionGroup;

template<typename T>
class RayChecker{
public:
    virtual gly_float AllowedHorizontalMove(const gly_float& attempt, RayCollisionGroup* group) const = 0;
    virtual gly_float AllowedVerticalMove(const gly_float& attempt, RayCollisionGroup* group) const = 0;
    virtual ss::vec2<gly_float> AllowedMove(const ss::vec2<gly_float>& attempt, RayCollisionGroup* group) const = 0;
};

}

#endif