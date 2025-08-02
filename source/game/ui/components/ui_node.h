#pragma once

#include "core/math/rect.h"
#include <vector>

class App;

namespace ui
{
class UiNode
{
public:
    UiNode(UiNode* parent = nullptr);
    virtual ~UiNode() = default;

    UiNode* GetParent();
    void SetParent(UiNode* parent);

    virtual void RemoveChild(UiNode* child);
    virtual void AddChild(UiNode* child);

    int GetChildsCount() const;
    UiNode* GetChild(int index);
    const UiNode* GetChild(int index) const;
    void SetChild(int index, UiNode* ui_node);
    
    template<typename T>
    T* GetChild(int index)
    {
        return static_cast<T*>(GetChild(index));
    }

    Point GetPos() const;
    Point GetAbsPos() const;
    void SetPos(const Point& pos);
    
    const Rect& GetBoundBox() const;
    virtual Rect ComputeBoundBox() const;

    const Rect& GetMargin() const;
    void SetMargin(const Rect& margin);

    bool IsVisible() const;
    void SetVisible(bool v);

    virtual void Update(App& app);
    virtual void Draw(App& app);

protected:
    void SetDirty();
    bool IsDirty() const;
    void ResizeChilds(int size);
private:
    void DebugDraw(App& app);

    UiNode* m_parent{};
    std::vector<UiNode*> m_childs{};
    
    Point m_pos{};
    Rect m_margin{2, 2, 2, 2};
    mutable Rect m_boundbox{};
    mutable bool m_dirty{true};
    bool m_visible{true};
};
} // namespace ui