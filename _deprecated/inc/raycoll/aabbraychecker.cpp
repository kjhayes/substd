#include<Glewy/Standard/RayCollisions/aabbraychecker.hpp>

#include<substd/transform.hpp>
#include<substd/rect.hpp>
#include<substd/util.hpp>
#include<substd/math.hpp>

#include<Glewy/Standard/RayCollisions/raycollisiongroup.hpp>

#include<Glewy/Debug/debugrendercalls.hpp>

namespace gly{

gly_float AABBRayChecker::AllowedHorizontalMove(const gly_float& attempt, RayCollisionGroup* group) const {
    
}
gly_float AABBRayChecker::AllowedVerticalMove(const gly_float& attempt, RayCollisionGroup* group) const {
    if(attempt == 0.0f){return attempt;}
    ss::Rect<gly_float> rect = transform->GetGlobalRect();
    gly_float curr_mag = ss::Math::Abs(attempt);
    if(attempt > 0){
        ss::vec2<gly_float> tl = rect.GetCorner(ss::CORNER_TOP_LEFT);
        std::list<ss::vec2<gly_float>> l = ss::PointsBetween(tl, tl+ss::vec2<gly_float>(rect.dimensions.x, 0.0f), vertical_resolution);
        for(auto iter = l.begin(); iter != l.end(); iter++){
            ss::VerticalDirRay<gly_float> ray(*iter, curr_mag);
            curr_mag = group->VerticalCollide(ray);
        }
        return curr_mag;
    }
    else{ //attempt < 0
        ss::vec2<gly_float> bl = rect.GetCorner(ss::CORNER_BOTTOM_LEFT);
        std::list<ss::vec2<gly_float>> l = ss::PointsBetween(bl, bl+ss::vec2<gly_float>(rect.dimensions.x, 0.0f), vertical_resolution);
        for(auto iter = l.begin(); iter != l.end(); iter++){
            ss::VerticalDirRay<gly_float> ray(*iter, -curr_mag);
            curr_mag = group->VerticalCollide(ray);
        }
        return -curr_mag;
    }
}
ss::vec2<gly_float> AABBRayChecker::AllowedMove(const ss::vec2<gly_float>& attempt, RayCollisionGroup* group) const{
    ss::vec2<gly_float> dis;
    ss::vec2<gly_float> start_pos = transform->GetLocalPosition();
    dis.x = AllowedHorizontalMove(attempt.x, group);
    transform->SetLocalPositionX(start_pos.x + dis.x);
    dis.y = AllowedVerticalMove(attempt.y, group);
    transform->SetLocalPositionX(start_pos.x);
    return dis;
}

}