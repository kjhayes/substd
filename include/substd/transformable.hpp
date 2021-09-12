#ifndef SUBSTD_TRANSFORMABLE_HPP
#define SUBSTD_TRANSFORMABLE_HPP

namespace ss{

class Transform;

class Transformable
{
protected:
    ss::Transform* transform;
public:
    Transformable();
    Transformable(Transform* parent);
    ~Transformable();
    Transform* GetTransform();
};

}

#endif //SUBSTD_TRANSFORMABLE_HPP