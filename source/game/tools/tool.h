#pragma once

#include "core/math/point.h"

namespace guimp
{
class Canvas;

class Tool
{
public:
    virtual ~Tool() = default;
    virtual void Use(const Point& position, Canvas& canvas) = 0;
    virtual void End() = 0;
};
} // namespace guimp