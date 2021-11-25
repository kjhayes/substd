#ifndef SUBSTD_MAT_HPP
#define SUBSTD_MAT_HPP

#include<algorithm>
#include<functional>

#include<substd/math.hpp>
#include<substd/vec.hpp>

namespace ss
{

/**
 * @class mat
 * 
 * @tparam T type of the matrix scalar
 * @tparam r number of matrix rows
 * @tparam c number of matrix columns
 */
template<typename T, size_t r, size_t c = r>
class mat : public std::array<ss::vec<T,r>,c> {
protected:
    using M = mat<T, r, c>;
    using Col = vec<T, r>;
    using Row = vec<T, c>;
    using RowRef = vec<T&, c>;

    RowRef GetRowRef(const size_t& index) {
        RowRef ret;
        for(size_t i = 0; i < c; i++){
            ret[i] = this->at(i)[index];
        }
        return ret;
    }

    vec<Col, c> AsVecOfVec() const {
        return vec<Col,c>(((std::array<Col, c>)*this));
    };

public:
    /**
     * @brief Default Constructor
     */
    mat(){}
    /**
     * @brief Identity Constructor
     * 
     * @param t Value to Set Matrix Diagonal 
     */
    mat(const T& t){
        if constexpr(r >= c){
            for(size_t col = 0; col < c; col++){
                this->at(col) = Col::Unit(col, t);
            }
        }
        else {
            for(size_t row = 0; row < r; row++){
                this->at(row) = Col::Unit(row, t);
            }
        }
    }

    ///@fn Sum
    template<typename OT, size_t Or, size_t Oc>
    M Sum(const mat<OT, Or, Oc>& other) const;
    ///@fn Dif
    template<typename OT, size_t Or, size_t Oc>
    M Dif(const mat<OT, Or, Oc>& other) const;
    ///@fn Prod
    template<typename S>
    M Prod(const S& scalar) const;
    ///@fn Quot
    template<typename S>
    M Quot(const S& scalar) const;
    ///@fn LeftProd
    template<typename S>
    M LeftProd(const S& scalar) const;
    ///@fn LeftQuot
    template<typename S>
    M LeftQuot(const S& scalar) const;
    
    ///@fn Add
    template<typename OT, size_t Or, size_t Oc>
    void Add(const mat<OT, Or, Oc>& other);
    ///@fn Sub
    template<typename OT, size_t Or, size_t Oc>
    void Sub(const mat<OT, Or, Oc>& other);
    ///@fn Mul
    template<typename S>
    void Mul(const S& scalar);
    ///@fn Div
    template<typename S>
    void Div(const S& scalar);
    ///@fn LeftMul
    template<typename S>
    void LeftMul(const S& scalar);
    ///@fn LeftDiv
    template<typename S>
    void LeftDiv(const S& scalar);
    
    /**
     * @fn GetRow
     * 
     * @param index Index To Retrieve 
     * @return Row A Copy of the Row at index
     * @remark Only returns a copy of the row, and because columns are given preference within matrices,
     * this function will be less importantly optimized than retrieving columns. For instance, columns
     * will usually be stored contiguously as opposed to rows.
     */
    Row GetRow(const size_t& index) const {
        Row ret;
        for(size_t i = 0; i < c; i++){
            ret[i] = this->at(i)[index];
        }
        return ret;
    }
    
    /**
     * @fn GetColumn
     * 
     * @param index Index To Retrive
     * @return Col A Copy of the Column at index
     * @remark Should be functionally equivalent to the inherited function std::array::at() and the operator [].
     */
    Col GetColumn(const size_t& index) const {
        return this->at(index);
    }

    ///@fn MatProd
    template<typename OT, size_t Or, size_t Oc>
    M MatProd(const mat<OT, Or, Oc>& other) const {
        M ret;
        for(size_t col = 0; col < c; col++){
            for(size_t row = 0; row < r; row++){
                ret[col][row] = this->GetRow(row).Dot(other[col]);
            }
        }
        return ret;
    }
    ///@fn MatMul
    template<typename OT, size_t Or, size_t Oc>
    void MatMul(const mat<OT, Or, Oc>& other) {
        M prod = MatProd(other);
        for(size_t col = 0; col < c; col++){
            this->at(col) = other->at(col);
        }
    }
    ///@fn VecProd
    template<typename OT, size_t Odim>
    Col VecProd(const vec<OT, Odim>& v) const {
        return AsVecOfVec().Dot(v);
    }

    //Operators
    
    template<typename OT, size_t Or, size_t Oc>
    M operator+(const mat<OT, Or, Oc>& other) const {return Sum(other);}  
    template<typename OT, size_t Or, size_t Oc>
    void operator+=(const mat<OT, Or, Oc>& other) {Add(other);}
    template<typename OT, size_t Or, size_t Oc>
    M operator-(const mat<OT, Or, Oc>& other) const {return Dif(other);}
    template<typename OT, size_t Or, size_t Oc>
    void operator-=(const mat<OT, Or, Oc>& other) {Sub(other);}

    template<typename OT, size_t Odim>
    Col operator*(const vec<OT, Odim>& v) const {return VecProd(v);}
    template<typename OT, size_t Or, size_t Oc>
    M operator*(const mat<OT, Or, Oc>& other) const {return MatProd(other);}
    template<typename OT, size_t Or, size_t Oc>
    void operator*=(const mat<OT, Or, Oc>& other){MatMul(other);} 

    template<typename S>
    M operator*(const S& scalar) const {return Prod(scalar);}
    //template<typename S>
    //friend S operator*(const S& scalar,const M& m){return m.LeftProd(scalar);}
    template<typename S>
    void operator*=(const S& scalar) {Mult(scalar);}
    
    template<typename S>
    M operator/(const S& scalar) const {return Quot(scalar);}
    //template<typename S>
    //friend S operator/(const S& scalar,const M& m){return m.LeftQuot(scalar);}
    template<typename S>
    void operator/=(const S& scalar) {Div(scalar);}

#ifndef SS_MAT_OSTREAM_ROW_END
#define SS_MAT_OSTREAM_ROW_END "\n"
#endif

    friend std::ostream& operator<<(std::ostream& o, const M& m)
    {
        for(size_t row = 0; row < m.NumberOfRows(); row++){
            Row curr = m.GetRow(row);
            o<<"["<<curr[0];
            for(size_t i = 1; i < curr.Dimension(); i++){
                o<<", "<<curr[i];
            }
            o<<"]"<<SS_MAT_OSTREAM_ROW_END;
        }
        return o;
    }

//static
    static constexpr size_t NumberOfRows() { return r; }
    static constexpr size_t NumberOfColumns() { return c; }
};

//These Functions Are Limiting Transform's Potentcial, 
//I should try to figure out a generic way to generate rotation matrices
//but I'm too lazy rn so this will work for what I need right now.

///@fn CreateRotationMatrix
template<typename T, size_t dim>
mat<T,dim> CreateRotationMatrix(const vec<T,(dim*(dim-1))/2>);

template<typename T>
mat<T, 2> CreateRotationMatrix<T,2>(const vec<T,1>& rot){
    if(rot == 0){return mat<T,2>(1);}
    else{
        mat<T, 2> ret;
        ss_trig cos, sin;
        cos = ss::Cos(rot[0]);
        sin = ss::Sin(rot[0]);
        ret[0][0] = cos;
        ret[0][1] = sin;
        ret[1][0] = -sin;
        ret[1][1] = cos;
        return ret;
    }
}

template<typename T>
mat<T, 3> CreateRotationMatrix<T,3>(const vec<T,3>& rot){
    mat<T, 3> ret(1);
    ss_trig cos, sin;
    if(rotation[2] != (T)0)
    {
        cos = ss::Cos(rotation[2]);
        sin = ss::Sin(rotation[2]);
        ret[0][0] = cos;
        ret[0][1] = sin;
        ret[1][0] = -sin;
        ret[1][1] = cos;
    }
    if(rotation[1] != (T)0)
    {
        cos = ss::Cos(rotation[1]);
        sin = std::sin(rotation[1]);
        mat<T,3> yrot;
        yrot[0][0] = cos;
        yrot[0][2] = -sin;
        yrot[2[[0] = sin;
        yrot[2[[2] = cos;
        ret = yrot*ret;
    }
    if(rotation[0] != (T)0)
    {
        cos = std::cos(rotation[0]);
        sin = std::sin(rotation[0]);
        mat<T,3> xrot;
        xrot[1][1] = cos;
        xrot[1][2] = sin;
        xrot[2[[1] = -sin;
        xrot[2[[2] = cos;
        ret = xrot*ret;    
    }
    return ret;
}

}

#endif // SUBSTD_MAT_HPP