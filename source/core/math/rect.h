#pragma once

#include "point.h"
#include <SDL_rect.h>

using Rect = SDL_Rect;

bool Contains(const Rect& rect, const Point& point);
bool Intersect(const Rect& rect, const Rect& other);
Rect Expand(const Rect& rect, const Rect& other);
Point Center(const Rect& rect);