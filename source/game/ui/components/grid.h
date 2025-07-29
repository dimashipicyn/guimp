#pragma once

#include "ui_node.h"
#include "core/math/point.h"
#include "core/math/size.h"
#include <initializer_list>

namespace ui
{
class Grid : public UiNode
{
public:
    Grid(const Size& cells_count, std::initializer_list<UiNode*> cells = {});
    UiNode* GetCell(const Point& pos);
    const UiNode* GetCell(const Point& pos) const;
    void SetCell(const Point& pos, UiNode* cell);
private:
    Rect ComputeBoundBox() const override;
    void SetCellPositions();
    int GetCellIndex(const Point& pos);
    Point GetPosFromIndex(int index);

    Size m_size{};
    int m_margin{0};
    Size m_cell_size{0, 0};
};
} // namespace ui