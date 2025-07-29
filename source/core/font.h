#pragma once

#include "color.h"
#include "math/point.h"
#include "math/size.h"

#include <memory>

class Font
{
public:
    Font();
    ~Font();
    Font(const char* font_path);
    void Load(const char* font_path);
    void Draw(const Point& pos, const char* text);
    void SetScale(float scale);
    Size CalcTextSize(const char* text) const;
    void SetColor(const Color& color);

private:
    struct Impl;
    std::shared_ptr<Impl> m_impl {};
};