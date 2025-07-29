#pragma once

#include "ui_node.h"
#include "core/color.h"
#include <string>

class App;

namespace ui
{
class Label : public UiNode
{
public:
    Label(std::string text);
    const Color& GetColor() const;
    void SetColor(const Color& c);
private:
    void Draw(App& app) override;
    Rect ComputeBoundBox() const override;

    std::string m_text {};
    std::string m_font_name { "fonts/minogram_6x10.xml" };
    Color m_color { Colors::DARK_GRAY };
};
} // namespace ui