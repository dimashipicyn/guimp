#include "menu.h"
#include "button.h"
#include "core/color.h"
#include "stackable.h"
#include "ui_node.h"

#include "core/math/rect.h"
#include "core/app.h"

namespace ui
{
Menu::Menu(const char* title, std::initializer_list<UiNode*> items)
{
    auto* title_button = new Button(title);
    title_button->OnClick([this](Button&){
        m_active = true;
        for (int i = 1; i < GetChildsCount(); i++)
            GetChild(i)->SetVisible(true);
    });

    UiNode::AddChild(title_button);
    
    Stackable* stackable = new Stackable(ui::Stackable::Vertical);
    stackable->SetPos({0, title_button->GetBoundBox().h});
    UiNode::AddChild(stackable);

    for (UiNode* item : items)
        stackable->AddChild(item);
}

void Menu::AddChild(UiNode* item)
{
    GetChild(1)->AddChild(item);
}

void Menu::Update(App& app)
{
    const Rect& bb = GetBoundBox();
    if (!Contains(bb, app.Input->MousePosition()))
    {
        m_active = false;
        for (int i = 1; i < GetChildsCount(); i++)
            GetChild(i)->SetVisible(false);
    }

    UiNode::Update(app);
}

void Menu::Draw(App& app)
{
    if (m_active)
    {
        const Rect& bb = GetChild(1)->GetBoundBox();
        app.Renderer->DrawRect(bb, Colors::DARK_GRAY);
    }
    UiNode::Draw(app);
}

void MenuBar::Add(Menu* item)
{
    const Rect& bb = item->GetBoundBox();
    m_item_max_size.x = std::max(bb.w, m_item_max_size.x);
    m_item_max_size.y = std::max(bb.h, m_item_max_size.y);

    AddChild(item);
    SetItemsPositions();
}

void MenuBar::SetItemsPositions()
{
    for (int i = 0; i < GetChildsCount(); i++)
    {
        const Point pos{
            i * m_item_max_size.x,// + m_item_max_size.x / 2,
            0//m_item_max_size.y / 2,
        };
        GetChild(i)->SetPos(pos);
    }
}
} // namespace ui