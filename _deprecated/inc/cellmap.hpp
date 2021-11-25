#ifndef SUBSTD_CELLMAP_HPP
#define SUBSTD_CELLMAP_HPP

#include<substd/vec.hpp>
#include<substd/rect.hpp>
#include<substd/math.hpp>
#include<substd/typedef.hpp>
#include<vector>

namespace ss{


//Maps World Coordinates to Integral Cell Locations
class CellMap {
protected:
    typedef vec2<ss_int> CellPos;
    typedef vec2<ss_float> WorldPos;
    typedef vec2<ss_float> CellSize;
    typedef Rect<ss_float> WorldRect;

    CellSize cell_size;
    CellSize inverse_cell_size;

public:

    CellMap(const CellSize& size);
    
    void SetCellSize(const CellSize& size);
    CellSize GetCellSize() const;
    
    void SetInverseCellSize(const CellSize& inv_size);
    CellSize GetInverseCellSize() const;

    CellPos GetCellOf(const WorldPos& world_pos) const;
    WorldPos GetCellBottomLeft(const CellPos& cell_pos) const;
    WorldPos GetCellCenter(const CellPos& cell_pos) const;

    //Beware Using Any C++ version less than C++11 because there will be no move semantics
    std::vector<CellPos> GetOverlappingCells(const WorldRect& rect) const;
};

}
#endif