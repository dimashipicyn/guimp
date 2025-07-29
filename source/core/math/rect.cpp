#include "rect.h"

#include <SDL_rect.h>
#include <utility>

bool Contains(const Rect& rect, const Point& point)
{
    return SDL_PointInRect(&point, &rect);
}

bool Intersect(const Rect& rect, const Rect& other)
{
    return SDL_HasIntersection(&rect, &other);
}

Rect Expand(const Rect& rect, const Rect& other)
{
    int x1 = std::min(rect.x, other.x);
    int y1 = std::min(rect.y, other.y);
    int x2 = std::max(rect.x + rect.w, other.x + other.w);
    int y2 = std::max(rect.y + rect.h, other.y + other.h);

    return Rect {
        x1,
        y1,
        x2 - x1,
        y2 - y1,
    };
}

Point Center(const Rect& rect)
{
    return { rect.x + rect.w / 2, rect.y + rect.h / 2};
}