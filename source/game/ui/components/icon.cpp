#include "icon.h"

#include "core/app.h"
#include "core/provider.h"

namespace ui
{
Icon::Icon(const char* path, const Size& size)
{
    m_texture = Provider::Self().Assets()->GetTexture(path);
    if (size.x && size.y)
    {
        m_texture.Dest.w = size.x;
        m_texture.Dest.h = size.y;
    }
}

const Color& Icon::GetColor() const
{
    return *m_color;
}

void Icon::SetColor(const Color& c)
{
    m_color = c;
}

void Icon::Draw(App& app)
{
    if (m_color)
        m_texture.SetColor(*m_color);
    app.Renderer->DrawTexture(m_texture, GetAbsPos());
}

Rect Icon::ComputeBoundBox() const
{
    return {
        GetAbsPos().x - GetMargin().x,
        GetAbsPos().y - GetMargin().y,
        m_texture.Dest.w + GetMargin().w,
        m_texture.Dest.h + GetMargin().h
    };
}

} // namespace ui