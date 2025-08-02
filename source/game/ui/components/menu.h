#pragma once

#include "stackable.h"
#include "ui_node.h"
#include "button.h"

#include "core/math/size.h"
#include <initializer_list>
#include <vector>

namespace ui
{
class Menu : public UiNode
{
public:
    Menu(std::initializer_list<UiNode*> items = {});
    void AddChild(UiNode* item) override;

    void Draw(App& app) override;
private:
};

class MenuBar : public Stackable
{
public:
    MenuBar(UiNode* parent = nullptr);
    void Add(const char* title, Menu* item);

    void Update(App& app) override;
    void Draw(App& app) override;
private:
    void AddChild(UiNode* c) override { Stackable::AddChild(c); }

    std::vector<Menu*> m_menus{};
    Menu* m_current_active{};
};
} // namespace ui