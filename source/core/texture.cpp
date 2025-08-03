#include "texture.h"
#include "color.h"
#include <SDL_blendmode.h>
#include <SDL_render.h>

Texture::Texture(SDL_Texture* tex)
    : m_tex_handle(tex, SDL_DestroyTexture)
{
    if (!tex)
    {
        return;
    }

    if (SDL_QueryTexture(m_tex_handle.get(), NULL, NULL, &Src.w, &Src.h))
    {
        SDL_Log("Texture::SDL_QueryTexture() failed: %s\n", SDL_GetError());
    }

    Dest.w = Src.w;
    Dest.h = Src.h;

    SDL_SetTextureBlendMode( m_tex_handle.get(), SDL_BLENDMODE_BLEND);
}

// Color Texture::GetPixel(const Point& pos) const
// {
//     void* pixels = nullptr;
//     int pitch = 0;
//     if (SDL_LockTexture(m_tex_handle.get(), NULL, &pixels, &pitch) == 0)
//     {
//         Uint32* pixelData = (Uint32*)pixels;
        
//         const Color c = UintToColor(pixelData[pos.y * (pitch / 4) + pos.x]);
//         SDL_UnlockTexture(m_tex_handle.get());
//         return c;
//     }
//     return {};
// }

// void Texture::SetPixel(const Point& pos, const Color& color)
// {
//     void* pixels = nullptr;
//     int pitch = 0;
//     if (SDL_LockTexture(m_tex_handle.get(), NULL, &pixels, &pitch) == 0)
//     {
//         Uint32* pixelData = (Uint32*)pixels;
        
//         pixelData[pos.y * (pitch / 4) + pos.x] = ColorToUint(color);
//         SDL_UnlockTexture(m_tex_handle.get());
//     }
// }