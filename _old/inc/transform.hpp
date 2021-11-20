#ifndef SUBSTD_TRANSFORM_HPP
#define SUBSTD_TRANSFORM_HPP

#include<substd/tree.hpp>
#include<substd/mat.hpp>
#include<substd/modulo.hpp>
#include<substd/rect.hpp>

namespace ss
{

class Transform : public Tree
{
    friend class ITransformable;

    protected:
//Variables
        mutable bool localAABBHasChanged = true;
        mutable bool localRotationHasChanged = true;

        mutable bool parentHasChanged = true;
        mutable bool childrenAreNotified = true;

        vec3<ss_float> local_position;
        vec3<ss_float> local_scale;
        vec3<modulo_tau<ss_float>> local_rotation;

        mutable vec3<ss_float> global_position;

        mutable mat4<ss_float> localAABBMatrix;
        mutable mat4<ss_float> localRotationMatrix;
        mutable mat4<ss_float> localMatrix;
        
        mutable mat4<ss_float> globalMatrix;

//Methods
        virtual void CalculateLocalAABBMatrix() const;
        void CalculateLocalRotationMatrix() const;

        void CalculateLocalMatrix() const;

        Transform();
        Transform(Transform*);

    public:
        mat4<ss_float> GetLocalAABBMatrix() const;
        mat4<ss_float> GetLocalRotationMatrix() const;

        mat4<ss_float> GetLocalMatrix() const;
        mat4<ss_float> GetGlobalMatrix() const;

        virtual vec3<ss_float> GetLocalPosition() const;
        virtual void SetLocalPosition(const vec3<ss_float>&);
        
        virtual void SetLocalPositionX(const ss_float&);
        virtual void SetLocalPositionY(const ss_float&);
        virtual void SetLocalPositionZ(const ss_float&);

        virtual vec3<ss_float> GetGlobalPosition() const;
        virtual void SetGlobalPosition(const vec3<ss_float>&);

        virtual vec3<ss_float> GetLocalScale() const;
        virtual void SetLocalScale(const vec3<ss_float>&);

        virtual void SetLocalScaleX(const ss_float&);
        virtual void SetLocalScaleY(const ss_float&);
        virtual void SetLocalScaleZ(const ss_float&);

        virtual vec3<modulo_tau<ss_float>> GetLocalRotation() const;
        virtual void SetLocalRotation(const vec3<modulo_tau<ss_float>>&);

        virtual void SetLocalRotationX(const modulo_tau<ss_float>&);
        virtual void SetLocalRotationY(const modulo_tau<ss_float>&);
        virtual void SetLocalRotationZ(const modulo_tau<ss_float>&);

        Rect<ss_float> GetLocalRect() const;
        void SetLocalRect(const Rect<ss_float>&);

        Rect<ss_float> GetGlobalRect() const;

        void UpdateGlobals() const;

        Transform* GetParent() const;

        void NotifyChildren();

        void FlagLocalAABBChange();
        void FlagLocalRotationChange();
};

/*
class Transform : public Tree
{
    friend class Transformable;

    protected:
        bool AABBHasChanged = true;
        bool rotationHasChanged = true;

        bool parentHasChanged = true;
        bool childrenAreNotified = true;

        vec3<gly_float> position;
        vec3<gly_float> scale;
        vec3<modulo_tau<gly_float>> rotation;

        mat4<gly_float> aabbMatrix;
        mat4<gly_float> rotationMatrix;
        mat4<gly_float> local_matrix;
        mat4<gly_float> global_matrix;

        virtual void CalculateAABBMatrix();
        void CalculateRotationMatrix();

        void CalculateMatrix();

        Transform();
        Transform(Transform*);

    public:
        mat4<gly_float> AABBMatrix();
        mat4<gly_float> RotationMatrix();

        mat4<gly_float> LocalMatrix();
        mat4<gly_float> GlobalMatrix();

        virtual vec3<gly_float> GetPosition() const;
        virtual void SetPosition(const vec3<gly_float>&);
        
        virtual void SetPositionX(const gly_float&);
        virtual void SetPositionY(const gly_float&);
        virtual void SetPositionZ(const gly_float&);

        virtual vec3<gly_float> GetScale() const;
        virtual void SetScale(const vec3<gly_float>&);

        virtual void SetScaleX(const gly_float&);
        virtual void SetScaleY(const gly_float&);
        virtual void SetScaleZ(const gly_float&);

        virtual vec3<modulo_tau<gly_float>> GetRotation() const;
        virtual void SetRotation(const vec3<modulo_tau<gly_float>>&);

        virtual void SetRotationX(const modulo_tau<gly_float>&);
        virtual void SetRotationY(const modulo_tau<gly_float>&);
        virtual void SetRotationZ(const modulo_tau<gly_float>&);

        Rect<gly_float> GetRect();
        void SetRect(const Rect<gly_float>&);

        Transform* GetParent();

        void NotifyChildren();
};
*/
}

#endif