#ifndef SUBSTD_IMODIFIABLE_HPP
#define SUBSTD_IMODIFIABLE_HPP

namespace ss{

template<class T>
class IModifiable{
private:
    T value;
public:
    IModifiable(){value = EvalValue((T)0);}
    IModifiable(const T& t){value = EvalValue(t);}

    T GetValue(){return value;}
    void SetValue(const T& t){
        this->value = EvalValue(t);
    }
    virtual T EvalValue(const T& t){return t;}

    void operator=(const T& eq){SetValue(eq);}
    
    bool operator==(const T& other){return (value == EvalValue(other));}
    bool operator!=(const T& other){return (value != EvalValue(other));}

    T operator+(const T& other){return EvalValue(value+other);}
    T operator-(const T& other){return EvalValue(value-other);}
    T operator*(const T& other){return EvalValue(value*other);}
    T operator/(const T& other){return EvalValue(value/other);}
    T operator%(const T& other){return EvalValue(value%other);}
    
    void operator+=(const T& other){SetValue(value+other);}
    void operator-=(const T& other){SetValue(value-other);}
    void operator*=(const T& other){SetValue(value*other);}
    void operator/=(const T& other){SetValue(value/other);}
    void operator%=(const T& other){SetValue(value%other);} 

    operator T&(){return value;}  
    operator T() const {return value;}
};

}

#endif //GLEWY_IMODIFIABLE_HPP