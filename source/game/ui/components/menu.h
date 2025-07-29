#pragma once

#include "ui_node.h"
#include "button.h"

#include "core/math/size.h"
#include <initializer_list>

namespace ui
{
class MenuBar;
class Menu : public UiNode
{
public:
    Menu(const char* title, std::initializer_list<UiNode*> items = {});
    void AddChild(UiNode* item) override;

    void Update(App& app) override;
    void Draw(App& app) override;
private:
    bool m_active{false};
};

class MenuBar : public UiNode
{
public:
    void Add(Menu* menu);
private:
    void SetItemsPositions();
    Size m_item_max_size{};
};
} // namespace ui