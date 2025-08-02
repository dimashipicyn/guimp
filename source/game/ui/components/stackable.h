#pragma once

#include "ui_node.h"
#include <initializer_list>

namespace ui
{
class Stackable : public UiNode
{
public:
    enum Type
    {
        Horizontal,
        Vertical
    };

    Stackable(Type type = Horizontal, UiNode* parent = nullptr);
    Stackable(std::initializer_list<UiNode*> childs, Type type = Horizontal, UiNode* parent = nullptr);
    void AddChild(UiNode* item) override;
    void Update(App& app) override;
private:
    void UpdateLayout();
    Rect ComputeBoundBox() const override;

    Type m_type{Horizontal};
};
} // namespace ui