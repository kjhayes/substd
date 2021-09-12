#include<substd/transformable.hpp>

#include<substd/transform.hpp>

namespace ss{

Transformable::Transformable(){transform = new ss::Transform();}
Transformable::Transformable(ss::Transform* parent){transform = new ss::Transform(parent);}
Transformable::~Transformable(){delete transform;}
ss::Transform* Transformable::GetTransform(){
    return transform;
}

}