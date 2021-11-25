#include<substd/transform.hpp>

#include<cmath>

namespace ss
{

Transform::Transform():Tree(nullptr), local_scale(1.0f,1.0f,1.0f){}
Transform::Transform(Transform* parent):Tree(parent), local_scale(1.0f,1.0f,1.0f){}

void Transform::CalculateLocalAABBMatrix() const
{
    localAABBMatrix.t = vec4<ss_float>(local_position, 1.0f);

    localAABBMatrix.i.x = local_scale.x;
    localAABBMatrix.j.y = local_scale.y;
    localAABBMatrix.k.z = local_scale.z;
}

void Transform::CalculateLocalRotationMatrix() const
{
    localRotationMatrix.Identity();
    float cos, sin;
    if(local_rotation.z!=0.0f)
    {
        cos = std::cos(local_rotation.z);
        sin = std::sin(local_rotation.z);
        localRotationMatrix.i.x = cos;
        localRotationMatrix.i.y = sin;
        localRotationMatrix.j.x = -sin;
        localRotationMatrix.j.y = cos;
    }
    if(local_rotation.y!=0.0f)
    {
        cos = std::cos(local_rotation.y);
        sin = std::sin(local_rotation.y);
        mat4<ss_float> yrot;
        yrot.i.x = cos;
        yrot.i.z = -sin;
        yrot.k.x = sin;
        yrot.k.z = cos;
        localRotationMatrix = yrot*localRotationMatrix;
    }
    if(local_rotation.x!=0.0f)
    {
        cos = std::cos(local_rotation.x);
        sin = std::sin(local_rotation.x);
        mat4<ss_float> xrot;
        xrot.j.y = cos;
        xrot.j.z = sin;
        xrot.k.y = -sin;
        xrot.k.z = cos;
        localRotationMatrix = xrot*localRotationMatrix;    
    }
}

void Transform::CalculateLocalMatrix() const
{
    localMatrix = GetLocalAABBMatrix() * GetLocalRotationMatrix();
}

mat4<ss_float> Transform::GetLocalAABBMatrix() const
{
    if(localAABBHasChanged)
    {
        CalculateLocalAABBMatrix();
        localAABBHasChanged = false;
    }
    return localAABBMatrix;
}

mat4<ss_float> Transform::GetLocalRotationMatrix() const
{
    if(localRotationHasChanged)
    {
        CalculateLocalRotationMatrix();
        localRotationHasChanged = false;
    }
    return localRotationMatrix;
}

mat4<ss_float> Transform::GetLocalMatrix() const
{
    if(localAABBHasChanged || localRotationHasChanged)
    {CalculateLocalMatrix();}
    return localMatrix;
}

mat4<ss_float> Transform::GetGlobalMatrix() const
{
    UpdateGlobals();
    return globalMatrix;
}

vec3<ss_float> Transform::GetLocalPosition() const
{return local_position;}
void Transform::SetLocalPosition(const vec3<ss_float>& pos)
{if(local_position != pos){local_position = pos; FlagLocalAABBChange();}}
        
void Transform::SetLocalPositionX(const ss_float& x){
    if(local_position.x != x){local_position.x = x; FlagLocalAABBChange();}
}
void Transform::SetLocalPositionY(const ss_float& y){
    if(local_position.y != y){local_position.y = y; FlagLocalAABBChange();}
}
void Transform::SetLocalPositionZ(const ss_float& z){
    if(local_position.z != z){local_position.z = z; FlagLocalAABBChange();}
}

vec3<ss_float> Transform::GetGlobalPosition() const {
    UpdateGlobals();
    return global_position;
}
void Transform::SetGlobalPosition(const vec3<ss_float>& gp) {
    SetLocalPosition(GetGlobalMatrix().Inverse()*vec4<ss_float>(gp,1.0f));
}

vec3<ss_float> Transform::GetLocalScale() const
{return local_scale;}
void Transform::SetLocalScale(const vec3<ss_float>& scl)
{if(local_scale != scl){local_scale = scl; FlagLocalAABBChange();}}

void Transform::SetLocalScaleX(const ss_float& x){
    if(local_scale.x != x){local_scale.x = x; FlagLocalAABBChange();}
}
void Transform::SetLocalScaleY(const ss_float& y){
    if(local_scale.y != y){local_scale.y = y; FlagLocalAABBChange();}
}
void Transform::SetLocalScaleZ(const ss_float& z){
    if(local_scale.z != z){local_scale.z = z; FlagLocalAABBChange();}
}

vec3<modulo_tau<ss_float>> Transform::GetLocalRotation() const
{return local_rotation;}
void Transform::SetLocalRotation(const vec3<modulo_tau<ss_float>>& rot)
{if(local_rotation != rot){local_rotation = rot; FlagLocalRotationChange();}}

void Transform::SetLocalRotationX(const modulo_tau<ss_float>& x){
    if(local_rotation.x != x){local_rotation.x = x; FlagLocalRotationChange();}
}
void Transform::SetLocalRotationY(const modulo_tau<ss_float>& y){
    if(local_rotation.y != y){local_rotation.y = y; FlagLocalRotationChange();}
}
void Transform::SetLocalRotationZ(const modulo_tau<ss_float>& z){
    if(local_rotation.z != z){local_rotation.z = z; FlagLocalRotationChange();}
}

Rect<ss_float> Transform::GetLocalRect() const {
    return Rect<ss_float>(local_position, local_scale);
}
void Transform::SetLocalRect(const Rect<ss_float>& r){
    SetLocalPosition(vec3<ss_float>(r.center));
    SetLocalScale(vec3<ss_float>(r.dimensions));
}

Rect<ss_float> Transform::GetGlobalRect() const {
    return Rect<ss_float>(GetGlobalPosition(), GetLocalScale());
};

void Transform::UpdateGlobals() const {
    if(parent != nullptr){
        if(parentHasChanged){
            Transform* p = ((Transform*)parent);
            globalMatrix = GetLocalMatrix() * p->GetGlobalMatrix();
            global_position = globalMatrix.VecMult(vec4<ss_float>(local_position,1));
            parentHasChanged = false;
            p->childrenAreNotified = false;
        }
    }
    else{
        globalMatrix = GetLocalMatrix();
        global_position = local_position;
    }
}

Transform* Transform::GetParent() const
{
    return (Transform*)parent;
}

void Transform::NotifyChildren(){
    for(auto child = children.begin(); child != children.end(); child++){
        ((Transform*)(*child))->parentHasChanged = true;
    }
    childrenAreNotified = true;
}

void Transform::FlagLocalAABBChange(){
    localAABBHasChanged = true;
    if(!childrenAreNotified){NotifyChildren();}
}
void Transform::FlagLocalRotationChange(){
    localRotationHasChanged = true;
    if(!childrenAreNotified){NotifyChildren();}
}

}