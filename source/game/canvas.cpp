#include "canvas.h"

#include "core/app.h"
#include "core/color.h"
#include "core/provider.h"
#include "core/renderer.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>

namespace guimp
{
Canvas::Canvas(const Size& size)
    : m_raw_pixels(size.x * size.y)
{
    // Renderer* r = Provider::Self().Renderer();
    // m_texture = r->CreateTexture(size);

    // r->SetRenderTarget(m_raw_surface);
    // r->DrawFillRect({GetAbsPos().x, GetAbsPos().y, size.x, size.y}, Colors::WHITE);
    // r->SetRenderTarget({});

    int depth = 32; // e.g., for RGBA8888
    m_pitch = size.x * 4; // For contiguous pixel data

    // Example masks for RGBA8888 on a little-endian system
    // Adjust based on your actual pixel format and endianness
    Uint32 rmask = 0x000000FF;
    Uint32 gmask = 0x0000FF00;
    Uint32 bmask = 0x00FF0000;
    Uint32 amask = 0xFF000000;

    m_raw_surface = SDL_CreateRGBSurfaceFrom(m_raw_pixels.data(), size.x, size.y, depth, m_pitch, rmask, gmask, bmask, amask);
    m_raw_renderer = SDL_CreateSoftwareRenderer(m_raw_surface);

    SDL_Rect r{GetAbsPos().x, GetAbsPos().y, size.x, size.y};
    SDL_SetRenderDrawColor(m_raw_renderer, Colors::WHITE.r, Colors::WHITE.g, Colors::WHITE.b, Colors::WHITE.a);
    SDL_RenderFillRect(m_raw_renderer, &r);
}

Color Canvas::GetPixel(const Point& position) const
{
    // Renderer* r = Provider::Self().Renderer();
    // r->SetRenderTarget(m_texture);
    // const Color c = r->GetPixel(position);
    // r->SetRenderTarget({});
    return UintToColor(m_raw_pixels[position.y * (m_pitch / 4) + position.x]);
}

void Canvas::SetPixel(const Point& position, const Color& color)
{
    // Renderer* r = Provider::Self().Renderer();
    // r->SetRenderTarget(m_texture);
    // r->DrawPoint(position, color);
    // r->SetRenderTarget({});
    m_raw_pixels[position.y * (m_pitch / 4) + position.x] = ColorToUint(color);
}

void Canvas::SetLine(const Point& start, const Point& end, const Color& color)
{
    // Renderer* r = Provider::Self().Renderer();
    // r->SetRenderTarget(m_texture);
    // r->DrawLine(start, end, color);
    // r->SetRenderTarget({});
    SDL_SetRenderDrawColor(m_raw_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_raw_renderer, start.x, start.y, end.x, end.y);
}

Size Canvas::GetSize() const
{
    return { m_texture.Src.w, m_texture.Src.h };
}

void Canvas::Draw(App& app)
{
    m_texture = SDL_CreateTextureFromSurface(app.Renderer->m_renderer, m_raw_surface);
    app.Renderer->DrawTexture(m_texture);
}

} // namespace guimp