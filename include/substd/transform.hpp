#ifndef SUBSTD_TRANSFORM_HPP
#define SUBSTD_TRANSFORM_HPP

#include<substd/vec.hpp>
#include<substd/mat.hpp>
#include<substd/interfaces.hpp>
#include<substd/modulo.hpp>

namespace ss {

template<typename T, size_t dim>
class Plug : public virtual IPluggable<T, dim> {
protected:
    mat<T,dim+1> plugMatrix;

public:
    Plug() : plugMatrix(1) {}
    Plug(const vec<T,dim>& pos) : plugMatrix(1) {
        plugMatrix[dim] = pos;
    }
    Plug(const vec<T,dim>& pos, const vec<T,dim>& scale) : plugMatrix(1) {
        plugMatrix[dim] = pos;
        for(int i = 0; i < dim; i++){
            plugMatrix[i][i] = scale[i];
        }
    }

    vec<T,dim> GetPosition() const override {return vec<T,dim>(plugMatrix[dim])}
    virtual void SetPosition(const vec<T,dim>& val) override {plugMatrix[dim] = val}
    virtual void SetPosition(const T& val, const size_t& index) override {plugMatrix.at(dim).at(index) = val;}

    vec<T,dim> GetScale() const override {
        vec<T,dim> ret;
        for(int i = 0; i < dim; i++){
            ret[i] = plugMatrix[i][i];
        }
        return ret;
    }
    virtual void SetScale(const vec<T,dim>& val) override {
        for(int i = 0; i < dim; i++){
            plugMatrix[i][i] = val[i];
        }
    }
    virtual void SetScale(const T& val, const size_t& index) override {
        plugMatrix[index][index] = val;
    }

    mat<T,dim> GetPlugMatrix() const override {return plugMatrix;}
};

template<typename T, size_t dim>
class Rotation : public virtual IRotatable<T, dim> {
protected:
    bool rotationHasChanged;
    vec<T,NRP> rotation;
    volatile mat<T,dim+1> rotationMatrix;

    void CalculateRotationMatrix(){
        rotationMatrix = mat<T,dim+1>(0);
        rotationMatrix.at(dim).at(dim) = 1;
        rotationMatrix += CreateRotationMatrix<T,dim>(rotation);
        rotationHasChanged = false;
    }

public:
    Rotation() : rotationHasChanged(false), rotation(0), rotationMatrix(1) {}
    Rotation(const vec<T,dim>& rot) : rotation(rot), rotationHasChanged(true) {}

    vec<T,NRP> GetRotation() const override {return rotation;}
    vec<T,NRP> GetRotationMatrix() const override {
        if(rotationHasChanged){CalculateRotationMatrix();}
        return rotationMatrix;
    }
    virtual void SetRotation(const vec<T,NRP>& val) override {
        rotation = val;
        rotationHasChanged = true;
    }
    virtual void SetRotation(const T& val, const size_t& index) override {
        rotation[index] = val;
        rotationHasChanged = true;
    }
};

template<typename T, typename RT, size_t dim>
class Orientation : public virtual IOrientatable<T,RT,dim>, public Plug<T,dim>, public Rotation<RT,dim> {
protected:
    bool orientationHasChanged;
    mat<T,dim+1> orientationMatrix;

    void CalculateOrientationMatrix() const {
        orientationMatrix = GetPlugMatrix() * GetRotationMatrix();
        orientationHasChanged = false;
    };

public:
    Orientation(){}


    mat<T,dim+1> GetLocalMatrix() const override {
        if(orientationHasChanged){CalculateOrientationMatrix();}
        return orietationMatrix;
    }

//Overriding Inherited Setters
    void SetPosition(const vec<T,dim>& val) override {
        plugMatrix[dim] = val; 
        orientationHasChanged = true;
    }
    void SetPosition(const T& val, const size_t& index) override {
        plugMatrix.at(dim).at(index) = val;
        orientationHasChanged = true;    
    }
    void SetScale(const vec<T,dim>& val) override {
        for(int i = 0; i < dim; i++){
            plugMatrix[i][i] = val[i];
        }
        orientationHasChanged = true;
    }
    void SetScale(const T& val, const size_t& index) override {
        plugMatrix[index][index] = val;
        orientationHasChanged = true;
    }
    void SetRotation(const vec<RT,NRP>& val) override {
        rotation = val;
        rotationHasChanged = true;
        orientationHasChanged = true;
    }
    void SetRotation(const RT& val, const size_t& index) override {
        rotation[index] = val;
        rotationHasChanged = true;
        orientationHasChanged = true;
    }
};

template<typename T, typename RT, size_t dim>
class BaseTransform : public virtual ITransformable<T,dim>, public Orientation<T,RT,dim> {};
template<typename T, size_t dim>
using Transform = BaseTransform<T, modulo_tau<T>, dim>;

using Transform3d = Transform<double, 3>;
using Transform2d = Transform<double, 2>;
using Transform3f = Transform<float, 3>;
using Transform2f = Transform<float, 2>;

}

#endif//SUBSTD_TRANSFORM_HPP