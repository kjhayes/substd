#ifndef SUBSTD_RANGE_HPP
#define SUBSTD_RANGE_HPP

#include<algorithm>
#include<substd/vec.hpp>
#include<substd/typedef.hpp>

namespace ss{

typedef ss_float ss_midpoint;

template<class T>
class Range {
public:
    virtual void SetEndPoints(const vec2<T>&) = 0;

    virtual T GetMin() const = 0;
    virtual T GetMax() const = 0;

    virtual T GetSpan() const = 0;
    virtual ss_midpoint GetMidpoint() const = 0;
}; 

template<class T>
class BasicRange : public Range<T> {
protected:
    vec2<T> val;

public:
    BasicRange():val(0,1){}
    BasicRange(const T& a, const T& b){SetEndPoints({a,b});}
    BasicRange(const vec2<T>& v){SetEndPoints(v);}
    BasicRange(const T& zero_to){SetEndPoints({zero_to,0});}

    virtual void SetEndPoints(const vec2<T>& end_points) override {
        val = end_points;
        if(val.x>val.y){
            std::swap(val.x,val.y);
        }
    }

    virtual T GetMin() const override {return val.x;}
    virtual T GetMax() const override {return val.y;}

    virtual T GetSpan() const override {return val.y - val.x;}
    virtual ss_midpoint GetMidpoint() const override {return (ss_midpoint)((val.x+val.y)*0.5f);}
};

template<class T>
class MidpointRange : Range<T> {
protected:
    ss_midpoint midpoint;
    T span;
    virtual ss_midpoint GetHalfSpan() const {return ((ss_midpoint)span)*0.5;}

public:
    virtual void SetEndPoints(const vec2<T>& end_points) override {
        vec2<T> end_p = end_points;
        if(end_p.x > end_p.y){std::swap(end_p.x,end_p.y);}
        span = end_p.y - end_p.x;
        midpoint = (ss_midpoint)(end_p.x+end_p.y)*0.5;
    }

    virtual T GetMin() const override {return midpoint - GetHalfSpan();}
    virtual T GetMax() const override {return midpoint + GetHalfSpan();}

    virtual T GetSpan() const override {return span;};
    virtual ss_midpoint GetMidpoint() const override {return midpoint;};
}; 

template<class T>
class PreComputedRange : Range<T> {
protected:
    vec2<T> end_points;
    ss_midpoint midpoint;
    T span;
public:
    PreComputedRange():end_points(0,1),midpoint(0.5f),span(1){}
    PreComputedRange(const vec2<T>& r){SetEndPoints(r);}

    virtual void SetEndPoints(const vec2<T>& end_points) override {
        vec2<T> ep = end_points;
        if(ep.x>ep.y){std::swap(ep.x,ep.y);}
        span = ep.y-ep.x;
        midpoint = ((ss_midpoint)(ep.x+ep.y))*0.5;
    }

    virtual T GetMin() const override {return end_points.x;}
    virtual T GetMax() const override {return end_points.y;}

    virtual T GetSpan() const override {return span;}
    virtual ss_midpoint GetMidpoint() const override {return midpoint;}
};

template<class T>
class SortedRange : public BasicRange<T> {
public:
    SortedRange():BasicRange<T>(){}
    SortedRange(const T& a, const T& b):BasicRange<T>(a,b){}
    SortedRange(const vec2<T>& v):BasicRange<T>(v){}
    void SetEndPoints(const vec2<T>& end_points) override {
        BasicRange<T>::val = end_points;
    }
};

}

#endif