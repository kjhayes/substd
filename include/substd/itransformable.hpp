#ifndef SUBSTD_TRANSFORMABLE_HPP
#define SUBSTD_TRANSFORMABLE_HPP

namespace ss{

class Transform;

class ITransformable
{
protected:
    ss::Transform* transform;
public:
    ITransformable();
    ITransformable(Transform* parent);
    ~ITransformable();
    Transform* GetTransform();
};

}

#endif //SUBSTD_TRANSFORMABLE_HPP