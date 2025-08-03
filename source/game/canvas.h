#pragma once

#include "core/color.h"
#include "core/math/point.h"
#include "core/math/size.h"
#include "core/texture.h"
#include "game/ui/components/ui_node.h"
#include <SDL_render.h>
#include <SDL_surface.h>
#include <cstdint>


namespace guimp
{
class Canvas : public ui::UiNode
{
public:
    Canvas(const Size& size);
    Color GetPixel(const Point& position) const;
    void SetPixel(const Point& position, const Color& color);
    void SetLine(const Point& start, const Point& end, const Color& color);
    Size GetSize() const;

    void Draw(App& app) override;
private:
    Texture m_texture {};
    std::vector<uint32_t> m_raw_pixels;
    SDL_Surface* m_raw_surface{};
    SDL_Renderer* m_raw_renderer{};
    int m_pitch{};
};
} // namespace guimp