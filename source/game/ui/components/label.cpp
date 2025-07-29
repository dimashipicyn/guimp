#include "label.h"

#include "core/app.h"
#include "core/color.h"
#include "core/font.h"
#include "core/provider.h"


namespace ui
{
Label::Label(std::string text)
    : m_text(std::move(text))
{
}

const Color& Label::GetColor() const
{
    return m_color;
}

void Label::SetColor(const Color& c)
{
    m_color = c;
}

void Label::Draw(App& app)
{
    if (!IsVisible())
        return;
    
    Font font = app.Assets->GetFont(m_font_name);
    font.SetColor(m_color);
    font.Draw(GetAbsPos(), m_text.c_str());
}

Rect Label::ComputeBoundBox() const
{
    Font font = Provider::Self().Assets()->GetFont(m_font_name);
    const Size calc_size = font.CalcTextSize(m_text.c_str());
    return Rect{
        GetAbsPos().x - GetMargin().x,
        GetAbsPos().y - GetMargin().y,
        calc_size.x + GetMargin().w,
        calc_size.y + GetMargin().h
    };
}
} // namespace ui