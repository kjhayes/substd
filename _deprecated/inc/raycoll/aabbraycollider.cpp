#include<Glewy/Standard/RayCollisions/aabbraycollider.hpp>

#include<Glewy/Scene/entity.hpp>
#include<substd/transform.hpp>
#include<substd/intersection.hpp>

namespace gly{

AABBRayCollider::AABBRayCollider(Entity* e):Attachment(e){}

AABBRayCollider::RCReturnType AABBRayCollider::Collide(const RCRay& ray) const {
    return ray.GetMagnitude();
}

AABBRayCollider::RCReturnType AABBRayCollider::HorizontalCollide(const RCRay& ray) const {
    ss::vec2<RCType> bl = GetEntity()->GetTransform()->GetGlobalRect().GetCorner(ss::CORNER_BOTTOM_LEFT);
    ss::vec2<RCType> tr = GetEntity()->GetTransform()->GetGlobalRect().GetCorner(ss::CORNER_TOP_RIGHT);
    ss::vec2<RCType> origin = ray.GetOrigin();
    ss::vec2<RCType> dir = ray.GetDirection();
    
    if(!ss::Math::ExclusiveBetween(ss::SortedRange<RCType>(bl.y,tr.y), origin.y)){
        return ss::Math::Abs<RCType>(dir.x);
    }
    ss::SortedRange<RCType> x_range = ss::SortedRange<RCType>(bl.x,tr.x);
    if(ss::Math::ExclusiveBetween(x_range, origin.x)){return ss::Math::Abs<RCType>(dir.x);}
    else{
        return ss::Math::Abs<RCType>(ss::LinearRayHit<RCType>(origin.x, dir.x, ss::Math::Nearest<RCType>(x_range, origin.x)));
    }
}

AABBRayCollider::RCReturnType AABBRayCollider::VerticalCollide(const RCRay& ray) const {
    ss::vec2<RCType> bl = GetEntity()->GetTransform()->GetGlobalRect().GetCorner(ss::CORNER_BOTTOM_LEFT);
    ss::vec2<RCType> tr = GetEntity()->GetTransform()->GetGlobalRect().GetCorner(ss::CORNER_TOP_RIGHT);
    ss::vec2<RCType> origin = ray.GetOrigin();
    ss::vec2<RCType> dir = ray.GetDirection();
    if(!ss::Math::ExclusiveBetween(ss::SortedRange<RCType>(bl.x,tr.x), origin.x)){
        return ss::Math::Abs<RCType>(dir.y);
    }
    ss::SortedRange<RCType> y_range = ss::SortedRange<RCType>(bl.y,tr.y);
    if(ss::Math::ExclusiveBetween(y_range, origin.y)){return ss::Math::Abs<RCType>(dir.y);}
    else{
        return ss::Math::Abs<RCType>(ss::LinearRayHit<RCType>(origin.y, dir.y, ss::Math::Nearest<RCType>(y_range, origin.y)));
    }
}

}