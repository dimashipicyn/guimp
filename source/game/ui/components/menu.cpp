#include "menu.h"
#include "button.h"
#include "core/color.h"
#include "stackable.h"
#include "ui_node.h"

#include "core/math/rect.h"
#include "core/app.h"

namespace ui
{
Menu::Menu(std::initializer_list<UiNode*> items)
{
    Stackable* stackable = new Stackable(ui::Stackable::Vertical);
    UiNode::AddChild(stackable);
    for (UiNode* item : items)
        stackable->AddChild(item);
}

void Menu::AddChild(UiNode* item)
{
    GetChild(0)->AddChild(item);
}

void Menu::Draw(App& app)
{
    if (!IsVisible())
        return;
    const Rect& bb = GetChild(0)->GetBoundBox();
    app.Renderer->DrawFillRect(bb, Colors::BLACK);
    app.Renderer->DrawRect(bb, Colors::DARK_GRAY);
    UiNode::Draw(app);
}

MenuBar::MenuBar(UiNode* parent)
    : Stackable(Stackable::Horizontal, parent)
{
    UiNode::AddChild(new Stackable(Stackable::Horizontal));
}

void MenuBar::Add(const char* title, Menu* item)
{
    item->SetVisible(false);

    auto* title_button = new Button(title);
    title_button->OnClick([item, this](Button*){
        item->SetVisible(m_current_active != item);
        if (m_current_active)
        {
            m_current_active->SetVisible(false);
        }
        m_current_active = m_current_active != item ? item : nullptr;
    });
    AddChild(title_button);

    item->SetPos({title_button->GetAbsPos().x, title_button->GetBoundBox().h + title_button->GetMargin().h});
    m_menus.emplace_back(item);
}

void MenuBar::Update(App& app)
{
    // if (m_current_active)
    // {
    //     const Rect& bb = m_current_active->GetBoundBox();
    //     if (!Contains(bb, app.Input->MousePosition()))
    //     {
    //         m_current_active->SetVisible(false);
    //     }
    // }

    for (UiNode* m : m_menus)
        m->Update(app);

    UiNode::Update(app);
}

void MenuBar::Draw(App& app)
{
    for (UiNode* m : m_menus)
        m->Draw(app);

    UiNode::Draw(app);
}
} // namespace ui