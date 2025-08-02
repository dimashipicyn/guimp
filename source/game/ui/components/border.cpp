#include "border.h"

#include "core/app.h"
#include "core/color.h"
#include "game/ui/components/ui_node.h"

namespace ui
{
Border::Border(UiNode* parent)
    : UiNode(parent)
{
    
}

void Border::Draw(App& app)
{
    if (m_fill)
        app.Renderer->DrawFillRect(GetBoundBox(), Colors::DARK_GRAY);
    else
        app.Renderer->DrawRect(GetBoundBox(), Colors::DARK_GRAY);
    UiNode::Draw(app);
}

void Border::SetFill(bool v)
{
    m_fill = v;
}

void Border::SetColor(const Color& color)
{
    m_color = color;
}

} // namespace ui