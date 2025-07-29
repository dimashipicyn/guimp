#include "stackable.h"
#include "ui_node.h"

namespace ui
{
Stackable::Stackable(Type type, UiNode* parent)
    : UiNode(parent)
    , m_type(type)
{
}

void Stackable::AddChild(UiNode* item)
{
    const int childs = GetChildsCount();
    if (childs > 0)
    {
        const UiNode* last_child = GetChild(childs - 1);
        if (m_type == Horizontal)
        {
            item->SetPos(last_child->GetPos() + Point { last_child->GetBoundBox().w, 0 });
        }
        else
        {
            item->SetPos(last_child->GetPos() + Point { 0, last_child->GetBoundBox().h });
        }
    }
    UiNode::AddChild(item);
}

} // namespace ui