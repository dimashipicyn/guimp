#pragma once

#include "core/math/point.h"
#include "tool.h"
#include "core/color.h"
#include <optional>

namespace guimp
{
class Pencil : public Tool
{
public:
    void Use(const Point& position, Canvas& canvas) override;
    void End() override;
    void SetColor(const Color& color);
private:
    std::optional<Point> m_prev_position{};
    Color m_color{Colors::BLACK};
};
} // namespace guimp