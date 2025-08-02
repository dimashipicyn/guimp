#pragma once

#include "core/color.h"
#include "ui_node.h"
#include "core/texture.h"
#include <optional>

class App;

namespace ui
{
class Icon : public UiNode
{
public:
    Icon(const char* path, const Size& size = {});
    const Color& GetColor() const;
    void SetColor(const Color& c);

    void Draw(App& app) override;
private:
    Rect ComputeBoundBox() const override;

    Texture m_texture{};
    std::optional<Color> m_color{};
};
} // namespace ui