#pragma once

#include "ui_node.h"

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

    Stackable(Type type, UiNode* parent = nullptr);
    void AddChild(UiNode* item) override;

private:
    Type m_type{Horizontal};
};
} // namespace ui