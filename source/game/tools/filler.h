#pragma once

#include "core/color.h"
#include "tool.h"
#include <queue>

namespace guimp
{
class Filler : public Tool
{
public:
    void Use(const Point& position, Canvas& canvas) override;
    void End() override;

private:
    void Filling(const Point& position, Canvas& canvas);

    Color m_color{Colors::BLACK};
    Color m_replace_color{Colors::WHITE};
    bool m_used{false};
};
} // namespace guimp