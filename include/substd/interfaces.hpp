/**
 * @file
 * @author Kevin Hayes
 * @brief Various abstract class interfaces
 * @include list type_traits vec mat template graph
*/

#ifndef SUBSTD_INTERFACES_HPP
#define SUBSTD_INTERFACES_HPP

#include<list>
#include<type_traits>

#include<substd/vec.hpp>
#include<substd/mat.hpp>
#include<substd/template.hpp>
#include<substd/graph.hpp>

namespace ss{
/**
 * @class IRegistered
 * @brief derived classes are registered upon creation and removed on destruction
 * 
 * @tparam self Must be the inheriting class.
 * @tparam storage The storage class used for the registry. Must have functions storage::push_back(self*) and storage::remove(self*) defined.
 * 
*/
template<class self, class storage=std::list<self*>>
class IRegistered 
{
    CRTP_ASSERT(IRegistered, self);
public:
    /**
     * @var storage registry
     * @brief The registry containing all instances of this class
    */
    static storage registry;
    /**
     * @fn IRegistered
     * @brief calls registry.push_back() on this object.
    */
    IRegistered(){
        registry.push_back(reinterpret_cast<self*>(this));
    }
    /**
     * @fn ~IRegistered
     * @brief calls registry.remove() on this object before deletion
    */
    virtual ~IRegistered(){
        registry.remove(reinterpret_cast<self*>(this));
    }
};
template<class self, class storage> storage IRegistered<self, storage>::registry;

/**
 * @class IBindable
 * @brief Interface for objects which are singly bound to a global context.
 * 
 * @tparam self Must be the inheriting class.
 * 
 * @remark Useful for wrapper classes meant for API's such as OpenGL which have a global context and functions act on the currently bound object.
*/
template<class self>
class IBindable {
    CRTP_ASSERT(IBindable, self);
private:
    static IBindable<self>* currently_active;
public:
    /**
     * @fn SmartBind
     * @brief Calls Bind() only if this object is not the currently bound instance.
    */
    void SmartBind(){
        if(this != currently_active){
            this = currently_active;
            Bind();
        }
    }
    /**
     * @fn IsBound
     * @return bool indicating whether or not this object is the currently bound object.
    */
    bool IsBound() const {
        return this == currently_active;
    }
    /**
     * @fn Bind
     * @brief Binds the object globally.
    */
    void Bind() = 0;

    /**
     * @fn GetCurrentlyBound
     * @return A pointer to the currently bound object. Note: If no object has been bound yet, it could return nullptr.
    */
    static IBindable<self>* GetCurrentlyBound(){
        return currently_active;
    }
};

template<class self> IBindable<self>* IBindable<self>::currently_active = nullptr;

/**
 * @class IConstrainable
 * @brief Base class for classes representing a value type with special behaviour/constraints.
 * @tparam T an arithmetic type: must have operators +,-,*,/ all defined for T, with the input type of T, returning a type T. T must also have == and != defined comparing against another T, and returning a bool.
*/
template<class T>
class IConstrainable{
    static_assert(!std::is_fundamental_v<T>() || std::is_scalar_v<T>(), 
        "ERROR: IConstrainable Requires Fundemental Types To Be Scalar!");
private:
    T value;
public:
    IConstrainable(){value = EvalValue((T)0);}
    IConstrainable(const T& t){value = EvalValue(t);}

    T GetValue(){return value;}
    void SetValue(const T& t){
        this->value = EvalValue(t);
    }
    /**
     * @fn EvalValue
     * @brief the map from type T to the derived class
     * @param t the input value to be evaluated
     * @return A value mapped to the range of values acceptable for the derived class
    */
    virtual T EvalValue(const T& t) const = 0;

    void operator=(const T& eq){SetValue(eq);}
    
    bool operator==(const T& other){return (value == EvalValue(other));}
    bool operator!=(const T& other){return (value != EvalValue(other));}

    T operator+(const T& other){return EvalValue(value+other);}
    T operator-(const T& other){return EvalValue(value-other);}
    T operator*(const T& other){return EvalValue(value*other);}
    T operator/(const T& other){return EvalValue(value/other);}
    
    void operator+=(const T& other){SetValue(value+other);}
    void operator-=(const T& other){SetValue(value-other);}
    void operator*=(const T& other){SetValue(value*other);}
    void operator/=(const T& other){SetValue(value/other);}

    operator T&(){return value;}  
    operator T() const {return value;}
};
/**
 * @class NoConstraint
 * @brief Trivial Instantiation of the IConstrainable interface with no contraints placed.
 */
template<typename T>
class NoConstraint : IConstrainable<T> {
public:
    T EvalValue(const T& t) const override (return t;)
};

//Transform Interfaces

template<typename T, size_t dim>
class IMatrixCalculable {
public:
    virtual mat<T,dim+1> GetLocalMatrix() const = 0;
    virtual mat<T,dim+1> GetGlobalMatrix() const {return GetLocalMatrix();}
};

///@class IPositionable
template<typename T, size_t dim>
class IPositionable {
public:
    virtual vec<T,dim> GetPosition() const = 0;
    virtual void SetPosition(const vec<T,dim>& val) = 0;
    virtual void SetPosition(const T& val, const size_t& index) = 0;
};

///@class IScalable
template<typename T, size_t dim>
class IScalable {
public:
    virtual vec<T,dim> GetScale() const = 0;
    virtual void SetScale(const vec<T,dim>& val) = 0;
    virtual void SetScale(const T& val, const size_t& index) = 0;
};

///@class IPluggable
template<typename T, size_t dim>
class IPluggable : public virtual IPositionable<T,dim>, public virtual IScalable<T,dim> {
    virtual mat<T,dim+1> GetPlugMatrix() const = 0;
};

///@class IRotatable
template<typename T, size_t dim>
class IRotatable {
public:
    constexpr size_t NRP = (dim*(dim-1))/2; //Number Of Rotational Planes

    virtual vec<T,NRP> GetRotation() const = 0;
    virtual mat<T,dim+1> GetRotationMatrix() const = 0;
    virtual void SetRotation(const vec<T,NRP>& val) = 0;
    virtual void SetRotation(const T& val, const size_t& index) = 0;
};

/**
 * @class IOrientatable
 */
template<typename T, typename RT, size_t dim>
class IOrientatable : public virtual IMatrixCalculable<T,dim>, public virtual IPluggable<T, dim>, public virtual IRotatable<RT, dim> {};
/**
 * @class ITransformable
 */
template<typename T, size_t dim>
class ITransformable : public virtual IMatrixCalculable, public Tree<ITransformable> {
protected:
    bool parentHasChanged;
    mat<T,dim+1> globalMatrix;

    void CalculateGlobalMatrix() const {
        globalMatrix = GetLocalMatrix() * GetParentMatrix();
        parentHasChanged = false;
    }

    mat<T,dim+1> GetParentMatrix() const {
        IMatrixCalculable* parent = reinterpret_cast<IMatrixCalculable*>(Tree<IMatrixCalculable>::GetParent());
        if(parent != nullptr){
            return parent->GetGlobalMatrix();
        }
        else{
            return mat<T,dim+1>(1);
        }
    }
    void NotifyChildren() {
        for(auto iter = this->begin(); iter != this->end(); iter++){
            (*(*ITransformable)iter).parentHasChanged = true;
            (*(*ITransformable)iter).NotifyChildren();
        }
    }

public:
    virtual mat<T,dim+1> GetGlobalMatrix() const override {
        if(parentHasChanged){CalculateGlobalMatrix();}
        return globalMatrix;
    }
};

/*
template<typename T, size_t dim>
class ITransformable {
public:
    mat<T, dim+1> GetLocalAABBMatrix() const;
    mat<T, dim+1> GetLocalRotationMatrix() const;
    mat<T, dim+1> GetLocalMatrix() const;
    mat<T, dim+1> GetGlobalMatrix() const;

    virtual vec3<T> GetGlobalPosition() const;
    virtual void SetGlobalPosition(const vec3<T>&);

    //Rect<T> GetLocalRect() const;
    //void SetLocalRect(const Rect<T>&);
    //Rect<T> GetGlobalRect() const;
    //void UpdateGlobals() const;
    //Transform* GetParent() const;
    //void NotifyChildren();
    //void FlagLocalAABBChange();
    //void FlagLocalRotationChange();
};
*/
}

#endif//SUBSTD_INTERFACES_HPP