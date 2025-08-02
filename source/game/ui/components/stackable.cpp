#include "stackable.h"
#include "core/math/rect.h"
#include "ui_node.h"

namespace
{
// int GetVerticalSpacing(ui::UiNode* a, ui::UiNode* b)
// {
//     return std::max(a->GetMargin().h, b->GetMargin().y);
// }

// int GetHorizontalSpacing(ui::UiNode* a, ui::UiNode* b)
// {
//     return std::max(a->GetMargin().w, b->GetMargin().x);
// }
} // namespace

namespace ui
{
Stackable::Stackable(Type type, UiNode* parent)
    : UiNode(parent)
    , m_type(type)
{
    SetMargin({});
}

Stackable::Stackable(std::initializer_list<UiNode*> childs, Type type, UiNode* parent)
    : Stackable(type, parent)
{
    for (UiNode* c: childs)
        UiNode::AddChild(c);
    UpdateLayout();
}

void Stackable::AddChild(UiNode* item)
{
    UiNode::AddChild(item);
    UpdateLayout();
}

void Stackable::Update(App& app)
{
    if (!IsVisible())
        return;

    UiNode::Update(app);
    if (IsDirty())
    {
        UpdateLayout();
    }
}

void Stackable::UpdateLayout()
{
    UiNode* prev = nullptr;
    for (int i = 0; i < GetChildsCount(); i++)
    {
        UiNode* item = GetChild(i);
        if (prev)
        {
            const Point offset = (m_type == Horizontal)
                ? Point { prev->GetPos().x + prev->GetBoundBox().w + item->GetMargin().x, item->GetMargin().y }
                : Point { item->GetMargin().x, prev->GetPos().y + prev->GetBoundBox().h + item->GetMargin().y };
            item->SetPos(offset);
        }
        else
        {
            const Point offset = Point { item->GetMargin().x, item->GetMargin().y };
            item->SetPos(offset);
        }
        prev = item;
    }
}

Rect Stackable::ComputeBoundBox() const
{
    Rect bb { GetAbsPos().x, GetAbsPos().y, 0, 0 };
    for (int i = 0; i < GetChildsCount(); i++)
    {
        const UiNode* child = GetChild(i);
        if (child && child->IsVisible())
        {
            Rect child_bb = child->ComputeBoundBox();
            child_bb.w += child->GetMargin().w;
            child_bb.h += child->GetMargin().h;
            bb = Expand(bb, child_bb);
        }
    }
    return bb;
}

} // namespace ui