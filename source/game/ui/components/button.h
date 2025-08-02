#pragma once

#include "core/math/rect.h"
#include "core/color.h"
#include "ui_node.h"
#include "icon.h"

#include <functional>
#include <string>
#include <variant>
#include <vector>

namespace ui
{
class Button : public UiNode
{
    using Callback = std::function<void(Button& /*self*/)>;
public:
    // Button(UiNode* parent = nullptr);
    Button(std::string text, UiNode* parent = nullptr);
    Button(UiNode* content, UiNode* parent = nullptr);
    void OnClick(Callback callback);
    
    void Update(App& app) override;
    void Draw(App& app) override;
private:
    Rect ComputeBoundBox() const override;
    void InvokeOnClick();
    
    std::vector<Callback> m_on_click_subs{};
    Color m_border_color{Colors::DARK_GRAY};
    bool m_filled{false};
    bool m_hovered{false};
    bool m_clicked{false};
    bool m_down{false};
};
} // namespace ui