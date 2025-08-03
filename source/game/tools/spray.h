#pragma once

#include "tool.h"

#include "core/color.h"
#include "core/math/point.h"

#include <optional>
#include <vector>

namespace guimp
{
class Spray : public Tool
{
public:
    void Use(const Point& position, Canvas& canvas) override;
    void End() override;

private:
    Point GenerateRandomPointInCircle(const Point& center, double radius);
    std::vector<Point> GenerateRandomPointsInCircle(int count, const Point& center, double radius);

    Color m_color{Colors::BLACK};
    float m_spray_effect{1.0};
};
} // namespace guimp