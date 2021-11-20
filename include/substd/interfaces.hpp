/**
 * @file
 * @author Kevin Hayes
 * @brief Various abstract class interfaces
 * @include list type_traits
*/

#ifndef SUBSTD_INTERFACES_HPP
#define SUBSTD_INTERFACES_HPP

#include<list>
#include<type_traits>

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
 * @class IModifiable
 * @brief Base class for classes representing a value type with special behaviour.
 * @tparam T an arithmetic type: must have operators +,-,*,/ all defined for T, with the input type of T, returning a type T. T must also have == and != defined comparing against another T, and returning a bool.
*/
template<class T>
class IModifiable{
    static_assert(std::is_scalar_v<T>());
private:
    T value;
public:
    IModifiable(){value = EvalValue((T)0);}
    IModifiable(const T& t){value = EvalValue(t);}

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
    virtual T EvalValue(const T& t){return t;}

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


}

#endif//SUBSTD_INTERFACES_HPP