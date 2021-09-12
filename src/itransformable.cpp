#include<substd/itransformable.hpp>

#include<substd/transform.hpp>

namespace ss{

ITransformable::ITransformable(){transform = new Transform();}
ITransformable::ITransformable(ss::Transform* parent){transform = new Transform(parent);}
ITransformable::~ITransformable(){delete transform;}
ss::Transform* ITransformable::GetTransform(){
    return transform;
}

}