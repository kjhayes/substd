#include<substd/cellmap.hpp>

#include<substd/corner.hpp>

namespace ss{

CellMap::CellMap(const CellSize& size):cell_size(size),inverse_cell_size(1.0f/size){}

void CellMap::SetCellSize(const CellSize& size){
    cell_size = size;
    inverse_cell_size = 1.0f/size;
}
CellMap::CellSize CellMap::GetCellSize() const {
    return cell_size;
}
void CellMap::SetInverseCellSize(const CellSize& inv_size){
    inverse_cell_size = inv_size;
    cell_size = 1.0f/inv_size;
}
CellMap::CellSize CellMap::GetInverseCellSize() const {
    return inverse_cell_size;
}

CellMap::CellPos CellMap::GetCellOf(const WorldPos& world_pos) const {
    return CellPos(
        Math::Floor(world_pos.x*inverse_cell_size.x),
        Math::Floor(world_pos.y*inverse_cell_size.y)
    );
}
CellMap::WorldPos CellMap::GetCellBottomLeft(const CellPos& cell_pos) const {
    return CellMap::WorldPos(
        cell_pos.x * cell_size.x,
        cell_pos.y * cell_size.y
    );
}
CellMap::WorldPos CellMap::GetCellCenter(const CellPos& cell_pos) const {
    return GetCellBottomLeft(cell_pos) + (cell_size*0.5f);
}

std::vector<CellMap::CellPos> CellMap::GetOverlappingCells(const WorldRect& rect) const {
    CellPos bl = GetCellOf(rect.GetCorner(CORNER_BOTTOM_LEFT));
    CellPos tr = GetCellOf(rect.GetCorner(CORNER_TOP_RIGHT));
    CellSize size = (tr-bl) + CellSize(1,1);
    std::vector<CellPos> ret;
    ret.reserve(size.x*size.y);
    for(int x = bl.x; x < bl.x+size.x; x++){
        for(int y = bl.y; y < bl.y+size.y; y++){
            ret.emplace_back(x,y);
        }
    }
    return ret;
}

}