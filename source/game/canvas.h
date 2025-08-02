#pragma once

#include "core/color.h"
#include "core/math/point.h"
#include "core/math/size.h"
#include "core/texture.h"
#include "game/ui/components/ui_node.h"


namespace guimp
{
class Canvas : public ui::UiNode
{
public:
    Canvas(const Size& size);
    void SetPixel(const Point& position, const Color& color);
    void SetLine(const Point& start, const Point& end, const Color& color);
    void Draw(App& app) override;
private:
    Texture m_texture {};
};
} // namespace guimp