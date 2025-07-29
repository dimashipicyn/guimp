#include "button.h"

#include "core/color.h"
#include "icon.h"
#include "label.h"
#include "ui_node.h"

#include "core/app.h"
#include "core/input.h"
#include "core/math/rect.h"

namespace ui
{
Button::Button(UiNode* parent)
    : UiNode(parent)
{
}

Button::Button(std::string text, UiNode* parent)
    : UiNode(parent)
{
    auto* l = new Label(text);
    AddChild(l);
}

Button::Button(Icon* icon, UiNode* parent)
    : UiNode(parent)
{
    AddChild(icon);
}

void Button::OnClick(Callback callback)
{
    m_on_click_subs.push_back(std::move(callback));
}

void Button::Update(App& app)
{
    if (!IsVisible())
        return;

    Point mouse = app.Input->MousePosition();
    const Rect& bb = GetBoundBox();
    if (Contains(bb, mouse))
    {
        m_hovered = true;
        m_clicked = app.Input->IsMouseClicked(MouseButton::Left);
        if (m_clicked)
            InvokeOnClick();
        m_down = app.Input->IsMouseDown(MouseButton::Left);
    }
    else
    {
        m_hovered = m_clicked = m_down = false;
    }
}

void Button::Draw(App& app)
{
    if (!IsVisible())
        return;

    const Rect& bb = GetBoundBox();
    if (m_filled)
    {
        app.Renderer->DrawFillRect(bb, m_border_color);
    }
    else if (m_hovered || m_down)
    {
        const Color color = m_down ? m_border_color * 0.8f : m_border_color * 1.2f;
        app.Renderer->DrawRect(bb, color);
    }
    UiNode::Draw(app);
}

Rect Button::ComputeBoundBox() const
{
    auto rect = UiNode::ComputeBoundBox();
    const Rect& margin = GetMargin();
    const Point& pos = GetAbsPos();
    return Rect { pos.x - margin.x, pos.y - margin.y, rect.w + margin.w, rect.h + margin.h };
}

void Button::InvokeOnClick()
{
    for (auto& cb : m_on_click_subs)
    {
        cb(*this);
    }
}
} // namespace ui