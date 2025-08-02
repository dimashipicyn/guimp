#include "ui_node.h"

#include "core/app.h"
#include "core/color.h"
#include "core/math/point.h"
#include "core/math/rect.h"
#include "core/ui.h"

#include <algorithm>

namespace ui
{
UiNode::UiNode(UiNode* parent)
{
    SetParent(parent);
}

UiNode* UiNode::GetParent()
{
    return m_parent;
}

void UiNode::SetParent(UiNode* parent)
{
    if (parent)
        parent->AddChild(this);
    m_parent = parent;
}

void UiNode::RemoveChild(UiNode* child)
{
    m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), child), m_childs.end());
    child->m_parent = nullptr;
}

void UiNode::AddChild(UiNode* child)
{
    m_childs.push_back(child);
    if (child->m_parent)
        child->m_parent->RemoveChild(child);
    child->m_parent = this;
}

int UiNode::GetChildsCount() const
{
    return m_childs.size();
}

UiNode* UiNode::GetChild(int index)
{
    return m_childs.at(index);
}

const UiNode* UiNode::GetChild(int index) const
{
    return const_cast<UiNode*>(this)->GetChild(index);
}

void UiNode::SetChild(int index, UiNode* ui_node)
{
    auto* old = std::exchange(m_childs.at(index), ui_node);
    delete old;
}

Point UiNode::GetPos() const
{
    return m_pos;
}

Point UiNode::GetAbsPos() const
{
    if (m_parent)
        return m_parent->GetAbsPos() + m_pos;
    return m_pos;
}

void UiNode::SetPos(const Point& pos)
{
    m_pos = pos;
    SetDirty();
}

void UiNode::Update(App& app)
{
    if (!IsVisible())
        return;
    for (UiNode* child : m_childs)
    {
        if (child)
            child->Update(app);
    }
}

void UiNode::Draw(App& app)
{
    if (!IsVisible())
        return;
    for (UiNode* child : m_childs)
    {
        if (child)
            child->Draw(app);
    }

    // DebugDraw(app);
}

const Rect& UiNode::GetBoundBox() const
{
    if (std::exchange(m_dirty, false))
    {
        m_boundbox = ComputeBoundBox();
    }
    return m_boundbox;
}

const Rect& UiNode::GetMargin() const
{
    return m_margin;
}

void UiNode::SetMargin(const Rect& margin)
{
    m_margin = margin;
}

bool UiNode::IsVisible() const
{
    return m_visible;
}

void UiNode::SetVisible(bool v)
{
    if (std::exchange(m_visible, v) != v)
        SetDirty();
}

Rect UiNode::ComputeBoundBox() const
{
    Rect bb { GetAbsPos().x, GetAbsPos().y, 0, 0 };
    for (const UiNode* child : m_childs)
    {
        if (child && child->IsVisible())
            bb = Expand(bb, child->ComputeBoundBox());
    }
    return bb;
}

void UiNode::SetDirty()
{
    m_dirty = true;

    auto* parent = m_parent;
    while (parent && !parent->m_dirty)
    {
        parent->m_dirty = true;
        parent = parent->m_parent;
    }

    for (int i = 0; i < GetChildsCount(); i++)
    {
        GetChild(i)->SetDirty();
    }
}

bool UiNode::IsDirty() const
{
    return m_dirty;
}

void UiNode::ResizeChilds(int size)
{
    m_childs.resize(size);
}

void UiNode::DebugDraw(App& app)
{
    const Rect& bb = GetBoundBox();
    app.Renderer->DrawRect(bb, Colors::PURPLE);

}
} // namespace ui