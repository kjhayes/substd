/**
 * @file
 * @author Kevin Hayes
 * @brief contains various cache class definitions
*/

#ifndef SUBSTD_CACHE_HPP
#define SUBSTD_CACHE_HPP

#include<vector>
#include<set>
#include<algorithm>

namespace ss{

/**
 * @class Cache
 * 
 * @brief abstract base class for Cache objects
 * 
 * Caches store CachedType (s) in buckets depending on GrouperType
 * 
 * @tparam GrouperType 
 * @tparam CachedType 
*/
template<class GrouperType, class CachedType> class Cache{
public:
    Cache(const GrouperType& grouper):grouper(grouper){}

    virtual bool IsEmpty() = 0;

    virtual void CacheThis(const CachedType& s) = 0;
    virtual void DecacheThis(const CachedType& s) = 0;

    const GrouperType grouper;
};

template<class GrouperType, class CachedType> class VectorCache : public Cache<GrouperType,CachedType>{
public:
    std::vector<CachedType> cache;

    VectorCache(const GrouperType& g):Cache<GrouperType,CachedType>(g){}

    bool IsEmpty(){
        if(this->cache.size() == 0){return true;}
        return false;
    }

    void CacheThis(const CachedType& s) override {this->cache.push_back(s);}
    void DecacheThis(const CachedType& s) override {this->cache.erase(std::find(cache.begin(), cache.end(), s));}
};

template<class GrouperType, class CachedType> class SetCache : public Cache<GrouperType,CachedType>{
public:
    std::set<CachedType> cache;

    SetCache(const GrouperType& g):Cache<GrouperType,CachedType>(g){}

    bool IsEmpty(){
        if(this->cache.size() == 0){return true;}
        return false;
    }

    void CacheThis(const CachedType& s) override {this->cache.insert(s);}
    void DecacheThis(const CachedType& s) override {this->cache.erase(s);}
};


}

#endif