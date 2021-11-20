#ifndef SUBSTD_MAT_HPP
#define SUBSTD_MAT_HPP

#include<substd/vec.hpp>

namespace ss
{

template<typename T> class mat2
{
public:
    vec2<T> i, j;
    mat2():
    i((T)1, (T)0),
    j((T)0, (T)1){}
    
    mat2(vec2<T> i, vec2<T> j):i(i), j(j){}
    
    vec2<T> RowX()const{return vec2<T>(i.x, j.x);}
    vec2<T> RowY()const{return vec2<T>(i.y, j.y);}

    vec2<T> VecMult(const vec2<T>& right)const{return vec2<T>(right.Dot(RowX()), right.Dot(RowY()));}
    mat2<T> MatMult(const mat2<T>& right)const
    {
        return mat2<T>(
            vec2<T>(right.i.Dot(RowX()), right.i.Dot(RowY())),
            vec2<T>(right.j.Dot(RowX()), right.j.Dot(RowY()))
            );
    }

    T MinorI() const {return j.y;}
    T MinorJ() const {return i.y;}

    T Determinant() const {
        //return (i.x*MinorI()/*.Determinant()*/-j.x*MinorJ()/*.Determinant*/;
        return (i.x*j.y)-(i.y*j.x);
    }

    mat2<T> Inverse() const {
        return mat2<T>();
    }

    void Identity()
    {
        i = vec2<T>((T)1,(T)0);
        j = vec2<T>((T)0,(T)1);
    }

    vec2<T> operator*(const vec2<T>& right)const{return VecMult(right);}
    mat2<T> operator*(const mat2<T>& right)const{return MatMult(right);}
};

template<typename T> class mat3
{
public:
    vec3<T> i, j, k;
    mat3():
        i((T)1, (T)0, (T)0),
        j((T)0, (T)1, (T)0),
        k((T)0, (T)0, (T)1){}

    mat3(vec3<T> i, vec3<T> j, vec3<T> k):i(i), j(j), k(k){}

    vec3<T> RowX()const{return vec3<T>(i.x, j.x, k.x);}
    vec3<T> RowY()const{return vec3<T>(i.y, j.y, k.y);}
    vec3<T> RowZ()const{return vec3<T>(i.z, j.z, k.z);}

    vec3<T> VecMult(const vec3<T>& right)const
    {return vec3<T>(right.Dot(RowX()), right.Dot(RowY()), right.Dot(RowZ()));}

    mat3<T> MatMult(const mat3<T>& right)const
    {
        return mat3<T>(
            vec3<T>(right.i.Dot(RowX()), right.i.Dot(RowY()), right.i.Dot(RowZ())),
            vec3<T>(right.j.Dot(RowX()), right.j.Dot(RowY()), right.j.Dot(RowZ())),
            vec3<T>(right.k.Dot(RowX()), right.k.Dot(RowY()), right.k.Dot(RowZ()))
            );
    }

    mat2<T> MinorI() const {
        return mat2<T>(
            {j.y,j.z},
            {k.y,k.z}
        );
    }
    mat2<T> MinorJ() const {
        return mat2<T>(
            {i.y,i.z},
            {k.y,k.z}
        );
    }
    mat2<T> MinorK() const {
        return mat2<T>(
            {i.y,i.z},
            {j.y,j.z}
        );
    }

    T Determinant() const {
/*
        return  (i.x * MinorI().Determinant()) - 
                (j.x * MinorJ().Determinant()) +
                (k.x * MinorK().Determinant());
*/
        return (
            (i.x*j.y*k.z)+ 
            (j.x*k.y*i.z)+
            (k.x*i.y*j.z)
            -(i.x*k.y*j.z)
            -(j.x*i.y*k.z)
            -(k.x*j.y*i.z)
        );
    }

    mat3<T> Inverse() const {
        return mat3<T>();
    }

    void Identity()
    {
        i = vec3<T>((T)1,(T)0,(T)0);
        j = vec3<T>((T)0,(T)1,(T)0);
        k = vec3<T>((T)0,(T)0,(T)1);
    }

    vec3<T> operator*(const vec3<T>& right)const{return VecMult(right);}
    mat3<T> operator*(const mat3<T>& right)const{return MatMult(right);}
};

template<typename T> class mat4
{
public:
    vec4<T> i, j, k, t;

    mat4():
        i((T)1,(T)0,(T)0,(T)0),
        j((T)0,(T)1,(T)0,(T)0),
        k((T)0,(T)0,(T)1,(T)0),
        t((T)0,(T)0,(T)0,(T)1){}

    mat4(vec4<T> i, vec4<T> j, vec4<T> k, vec4<T> t):i(i), j(j), k(k), t(t){}

    vec4<T> RowX()const{return vec4<T>(i.x, j.x, k.x, t.x);}
    vec4<T> RowY()const{return vec4<T>(i.y, j.y, k.y, t.y);}
    vec4<T> RowZ()const{return vec4<T>(i.z, j.z, k.z, t.z);}
    vec4<T> RowW()const{return vec4<T>(i.w, j.w, k.w, t.w);}

    vec4<T> VecMult(const vec4<T>& right) const
    {return vec4<T>(right.Dot(RowX()), right.Dot(RowY()), right.Dot(RowZ()), right.Dot(RowW()));}

    mat4<T> MatMult(const mat4<T>& right) const
    {
        return mat4(
            vec4<T>(right.i.Dot(RowX()), right.i.Dot(RowY()), right.i.Dot(RowZ()), right.i.Dot(RowW())),
            vec4<T>(right.j.Dot(RowX()), right.j.Dot(RowY()), right.j.Dot(RowZ()), right.j.Dot(RowW())),
            vec4<T>(right.k.Dot(RowX()), right.k.Dot(RowY()), right.k.Dot(RowZ()), right.k.Dot(RowW())),
            vec4<T>(right.t.Dot(RowX()), right.t.Dot(RowY()), right.t.Dot(RowZ()), right.t.Dot(RowW()))
        );
    }

    mat3<T> MinorI() const {
        return mat3<T>(
            {j.y,j.z,j.w},
            {k.y,k.z,k.w},
            {t.y,t.z,t.w}
        );
    }
    mat3<T> MinorJ() const {
        return mat3<T>(
            {i.y,i.z,i.w},
            {k.y,k.z,k.w},
            {t.y,t.z,t.w}
        );
    }
    mat3<T> MinorK() const {
        return mat3<T>(
            {i.y,i.z,i.w},
            {j.y,j.z,j.w},
            {t.y,t.z,t.w}
        );
    }
    mat3<T> MinorT() const {
        return mat3<T>(
            {i.y,i.z,i.w},
            {j.y,j.z,j.w},
            {k.y,k.z,k.w}
        );
    }

    T Determinant() const {
        return (
            i.x*MinorI().Determinant() -
            j.x*MinorJ().Determinant() +
            k.x*MinorK().Determinant() -
            t.x*MinorT().Determinant()
        );
    }

    mat4<T> Inverse() const {
        return mat4<T>();
    }

    void Identity()
    {
        i = vec4<T>((T)1,(T)0,(T)0,(T)0);
        j = vec4<T>((T)0,(T)1,(T)0,(T)0);
        k = vec4<T>((T)0,(T)0,(T)1,(T)0);
        t = vec4<T>((T)0,(T)0,(T)0,(T)1);
    }

    vec4<T> operator*(const vec4<T>& right)const{return VecMult(right);}
    mat4<T> operator*(const mat4<T>& right)const{return MatMult(right);}

/*
    void PerspectiveProjection
    (const vec2<T>& dim, const T& vfov, const T& near, const T& far)
    {
        this->Identity();
        const T halfTan = (T)tanf((vfov*0.00872664625)); //0.00872 ~ (pi/180)/2
        const T ar = dim.x/dim.y;
        const T range = near - far;

        i.x = ((T)1)/(halfTan*ar);
        j.y = ((T)1)/halfTan;
        k.z = (-near-far)/range;
        k.w = (T)1;
        t.z = (((T)2) * far * near) /range;
        t.w = (T)0;
    }
*/
};

}

#endif // GLEWY_MAT_HPP