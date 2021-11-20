#ifndef SUBSTD_RANGE_HPP
#define SUBSTD_RANGE_HPP

#include<algorithm>
#include<substd/vec.hpp>
#include<substd/constants.hpp>

namespace ss{

template<class T>
class Range {
public:
    Range(const T& a, const T& b);

    virtual T GetMin() const = 0;
    virtual void SetMin(const T&) = 0;
    virtual T GetMax() const = 0;
    virtual void SetMax(const T&) = 0;

    virtual T GetSpan() const = 0;

    template<typename M>
    virtual M GetMidpoint() const = 0;
}; 

}

#endif