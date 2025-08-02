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
// Button::Button(UiNode* parent)
//     : UiNode(parent)
// {
// }

Button::Button(std::string text, UiNode* parent)
    : UiNode(parent)
{
    auto* l = new Label(text);
    l->SetPos(Point{l->GetMargin().x, l->GetMargin().y });
    AddChild(l);
}

Button::Button(UiNode* content, UiNode* parent)
    : UiNode(parent)
{
    content->SetPos(Point{content->GetMargin().x, content->GetMargin().y });
    AddChild(content);
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
        m_down = app.Input->IsMouseDown(MouseButton::Left);
        m_clicked = app.Input->IsMouseClicked(MouseButton::Left);
        if (m_clicked)
            InvokeOnClick();
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
    app.Renderer->DrawFillRect(bb, Colors::GRAY);
    if (m_filled)
    {
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
    const Point& pos = GetAbsPos();
    return Rect {
        pos.x,
        pos.y,
        rect.w + GetChild(0)->GetMargin().w,
        rect.h + GetChild(0)->GetMargin().h
    };
}

void Button::InvokeOnClick()
{
    for (auto& cb : m_on_click_subs)
    {
        cb(this);
    }
}
} // namespace ui