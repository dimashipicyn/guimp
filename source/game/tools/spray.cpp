#include "spray.h"
#include "core/math/point.h"
#include "game/canvas.h"

#include <random>

namespace guimp
{
void Spray::Use(const Point& position, Canvas& canvas)
{
    auto points = GenerateRandomPointsInCircle(5 * m_spray_effect, position, 20);
    for (const Point& p : points)
        canvas.SetPixel(p, m_color);

    m_spray_effect += 0.03f;
}

void Spray::End()
{
    m_spray_effect = 1.0f;
}

Point Spray::GenerateRandomPointInCircle(const Point& center, double radius) {
    static std::mt19937 generator(std::random_device{}()); 
    static std::uniform_real_distribution<double> dist_0_1(0.0, 1.0);
    static std::uniform_real_distribution<double> dist_angle(0.0, 2.0 * M_PI); // M_PI is from <cmath> or define it

    double theta = dist_angle(generator);
    double r = radius * std::sqrt(dist_0_1(generator));

    int x = center.x + r * std::cos(theta);
    int y = center.y + r * std::sin(theta);

    return {x, y};
}

std::vector<Point> Spray::GenerateRandomPointsInCircle(int count, const Point& center, double radius)
{
    std::vector<Point> points(count);
    for (Point& p : points)
        p = GenerateRandomPointInCircle(center, radius);
    return points;
}
} // namespace guimp