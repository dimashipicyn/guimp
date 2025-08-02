#include "renderer.h"

#include "texture.h"
#include <SDL_hints.h>
#include <SDL_render.h>

Renderer::Renderer(int width, int height)
    : m_window_size{width, height}
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        SDL_Log("SDL_Init(SDL_INIT_VIDEO) failed: %s\n", SDL_GetError());
        return;
    }

    if (SDL_CreateWindowAndRenderer(m_window_size.x, m_window_size.y, 0, &m_window, &m_renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer() failed: %s\n", SDL_GetError());
        return;
    }

    /*const auto view = SDL_Rect { 0, 0, 50, 50 };
    SDL_RenderSetViewport(m_renderer, &view);*/
    // SDL_RenderSetScale(m_renderer, 10, 10);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

Texture Renderer::CreateTexture(const Size& size)
{
    return Texture(SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.x, size.y));
}

void Renderer::SetRenderTarget(Texture texture)
{
    SDL_SetRenderTarget(m_renderer, texture.m_tex_handle.get());
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::DrawTexture(const Texture& tex, const Point& dest)
{
    DrawTexture(tex, tex.Src, {dest.x, dest.y, tex.Dest.w, tex.Dest.h});
}

void Renderer::DrawTexture(const Texture& tex, const Rect& src, const Rect& dest)
{
    SDL_RenderCopy(m_renderer, tex.m_tex_handle.get(), &src, &dest);
}

void Renderer::DrawTexture(const Texture& tex)
{
    DrawTexture(tex, tex.Src, tex.Dest);
}
