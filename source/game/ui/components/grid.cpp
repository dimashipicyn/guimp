#include "grid.h"
#include "ui_node.h"

#include <assert.h>
#include <iostream>

namespace ui
{
Grid::Grid(const Size& cells_count, std::initializer_list<UiNode*> cells)
    : m_size(cells_count)
{
    assert(cells.size() <= static_cast<size_t>(m_size.x * m_size.y));
    ResizeChilds(m_size.x * m_size.y);
    for (size_t i = 0; i < cells.size(); i++)
        SetCell(GetPosFromIndex(i), *(cells.begin() + i));
}

UiNode* Grid::GetCell(const Point& pos)
{
    assert(pos.x * pos.y < m_size.x * m_size.y);
    return GetChild(GetCellIndex(pos));
}

const UiNode* Grid::GetCell(const Point& pos) const
{
    return const_cast<Grid*>(this)->GetCell(pos);
}

void Grid::SetCell(const Point& pos, UiNode* cell)
{
    assert(pos.x * pos.y < m_size.x * m_size.y);

    const Rect& bb = cell->GetBoundBox();
    m_cell_size.x = std::max(bb.w, m_cell_size.x);
    m_cell_size.y = std::max(bb.h, m_cell_size.y);

    cell->SetParent(this);
    SetChild(GetCellIndex(pos), cell);
    SetCellPositions();
}

Rect Grid::ComputeBoundBox() const
{
    const Rect bb = UiNode::ComputeBoundBox();
    return bb;
}

void Grid::SetCellPositions()
{
    // const int half_size_x_all = (m_size.x * m_cell_size.x + m_margin * (m_size.x + 1)) / 2;
    // const int half_size_y_all = (m_size.y * m_cell_size.y + m_margin * (m_size.x + 1)) / 2;
    
    for (int x = 0; x < m_size.x; x++)
    {
        for (int y = 0; y < m_size.y; y++)
        {
            UiNode* cell = GetCell({ x, y });
            if (!cell)
                continue;
            Point cell_pos {
                x * m_cell_size.x + m_margin + (x != 0 ? m_margin : 0),
                y * m_cell_size.y + m_margin + (y != 0 ? m_margin : 0)
            };
            printf("x: %d, y: %d\n", cell_pos.x, cell_pos.y);
            cell->SetPos(cell_pos);
        }
    }
}

int Grid::GetCellIndex(const Point& pos)
{
    return pos.y * m_size.x + pos.x;
}

Point Grid::GetPosFromIndex(int index)
{
    return {index % m_size.x, index / m_size.x};
}

} // namespace ui