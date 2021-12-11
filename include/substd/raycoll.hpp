#ifndef SUBSTD_RAYCOLL_HPP
#define SUBSTD_RAYCOLL_HPP

#include<substd/vec.hpp>
#include<substd/mat.hpp>
#include<substd/interfaces.hpp>
#include<substd/math.hpp>
#include<substd/util.hpp>

namespace ss{

/**
 * @fn PointsBetween
 * @return std::list<vec<T,dim>> List of n points in a line between a and b, inclusive.
 */
template<typename T, size_t dim>
std::list<vec<T,dim>> PointsBetween(const vec<T,dim>& a, const vec<T,dim>& b, const int& n){
    vec<T,dim> jump = (b-a) * (1/((T)(num-1)));
    std::list<vec<T,dim>> list;
    for(int i = 0; i<num; i++)
    {
	    list.push_back(a+(jump*i));
    }
    return list;
}

/**
 * @class RayMoveChecker
 */
template<typename T, size_t dim>
class RayMoveChecker : public virtual IPositionable<T, dim>, public virtual IMatrixCalculable<T,dim> {
protected:
    std::array<std::list<vec<T,dim>>dim> checkPoints;

public:
    virtual T AllowedMove(const size_t& dir, const T& move, const IRayCollidable& collidable){
        if(move == 0){return move;}
        MT curr_move = move;
        for(auto iter = checkPoints[dir].begin(); iter != checkPoints[dir].end(); iter++){
            curr_move = collidable->TrimMove(this->GetGlobalMatrix() * (*iter).Homogenized(), dir, curr_move);
            if(curr_move == 0){return curr_move;}
        }
        return curr_move;
    }
    virtual vec<T,dim> AllowedMove(const vec<T,dim>& move, const IRayCollidable& collidable) const {
        vec<T,dim> curr_move = move;
        for(size_t curr_dir = 0; curr_dir < dim; curr_dir++){
            curr_move[curr_dir] = AllowedMove(curr_dir, curr_move[curr_dir], collidable);
            this->AddPosition(curr_move[curr_dir], curr_dir);
        }
        this->AddPosition(curr_move * -1);
        return curr_move;
    }
    virtual vec<T,dim> MoveAsAllowed(const vec<T,dim>& move, const IRayCollidable& collidable) const {
        vec<T,dim> curr_move = move;
        for(size_t curr_dir = 0; curr_dir < dim; curr_dir++){
            curr_move[curr_dir] = AllowedMove(curr_dir, curr_move[curr_dir], collidable);
            this->AddPosition(curr_move[curr_dir], curr_dir);
        }
        return curr_move;
    }
};

///@class RectRayMoveChecker
template<typename T>
class AABBRayMoveChecker : public RayMoveChecker<T,2> {
public:
    RectRayMoveChecker(const int& horizontal_res, const int& vertical_res) {
        std::list<T> r = PointsBetween({0.5, -0.5}, [0.5, 0.5], vertical_res);
        std::list<T> l = PointsBetween({-0.5, -0.5}, [-0.5, 0.5], vertical_res);
        std::list<T> t = PointsBetween({-0.5, 0.5}, [0.5, 0.5], horizontal_res);
        std::list<T> b = PointsBetween({0.5, -0.5}, [-0.5, -0.5], horizontal_res);
        for(int v = 0; v < vertical_res; v++){
            RayMoveChecker<T,2>::checkPoints[0].push_back(r[v]);
            RayMoveChecker<T,2>::checkPoints[0].push_back[l[v]];
        }
        for(int h = 0; h < horizontal_res; h++){    
            RayMoveChecker<T,2>::checkPoints[1].push_back(t[h]);
            RayMoveChecker<T,2>::checkPoints[1].push_back[b[h]];
        }
    }
};

/**
 * @class IRayCollidable
 */
template<typename T, size_t dim>
class IRayCollidable {
public:
    virtual T TrimMove(const vec<T,dim>& origin, const size_t& dir, const T& move) const = 0;
};

///@class RayCollisionGroup
template<typename T, size_t dim>
class RayCollisionGroup : public IRayCollidable<T,dim> {
protected:
    std::list<IRayCollidable<T,dim>*> collidables;
public:
    void AddCollidable(IRayCollidable<T,dim>* coll){collidables.push_back(coll);}
    void RemoveCollidablee(IRayCollidable<T,dim>* coll){collidables.remove(coll);}

    T TrimMove(const vec<T,dim>& origin, const size_t& dir, const T& move) const override {
        T curr_move = move;
        for(auto iter = collidables.begin(); iter != collidables.end(); iter++){
            curr_move = (*iter)->TrimMove(origin, dir, curr_move);
        }
        return curr_move;
    }
};

///@class AABBRayCollidable
template<typename T>
class AABBRayCollidable : public virtual IRayCollidable<T,2>, public Plug<T,2> {
protected:
    T TrimHor(const T& origin, const T& move){

    }
    T TrimVer(const T& origin, const T& move){
        
    }

public:
    T TrimMove(const vec<T,2>& origin, const size_t& dir, const T& move) const override {
        if(dir == 0 && ss::ExclusiveBetween()){
            T half_ver_scale = GetScale(1) * 0.5;
            T ver_pos = GetPosition(1);
            if(ss::ExclusiveBetween(ver_pos-half_ver_scale, ver_pos+half_ver_scale, origin[1])){
                return TrimHor(origin[0], move);
            }
        }
        else{
            T half_hor_scale = GetScale(0) * 0.5;
            T hor_pos = GetPosition(0);
            if(ss::ExclusiveBetween(hor_pos-half_hor_scale, hor_pos+half_hor_scale, origin[0])){
                return TrimVer(origin[1], move);
            }
        }
        return move;
    }
};

}

#endif