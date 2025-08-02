#pragma once

#include "core/color.h"
#include "game/ui/components/ui_node.h"

namespace ui
{
class Border : public UiNode
{
public:
    Border(UiNode* parent = nullptr);
    void Draw(App& app) override;
    void SetFill(bool v);
    void SetColor(const Color& color);
private:
    Color m_color{Colors::BLACK};
    bool m_fill{false};
};
} // namespace ui