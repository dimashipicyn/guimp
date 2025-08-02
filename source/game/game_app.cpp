#include "game_app.h"

#include "constant.h"
#include "core/input.h"
#include "game/canvas.h"
#include "game/ui/components/ui_node.h"
#include "tools/pencil.h"
#include "tools/ui/tools_panel.h"
#include "ui/components/button.h"
#include "ui/components/icon.h"
#include "ui/components/label.h"
#include "ui/components/menu.h"
#include "ui/components/stackable.h"

void GameApp::OnInit()
{
    auto* file = new ui::Menu({
        new ui::Button(
            new ui::Stackable({
                new ui::Label("Open"),
                new ui::Icon("icons/editor/00000.png", {16,16})},
                ui::Stackable::Horizontal
            )
        ),
        new ui::Button("Save"),
        new ui::Button("Exit")
    });

    auto* edit = new ui::Menu;
    edit->AddChild(new ui::Button("Undo"));
    edit->AddChild(new ui::Button("Redo"));
    edit->AddChild(new ui::Button("Copy"));
    edit->AddChild(new ui::Button("Paste"));

    auto* menubar = new ui::MenuBar;
    menubar->Add("File", file);
    menubar->Add("Edit", edit);
    menubar->SetZIndex(1);

    m_root_ui = new ui::Stackable(ui::Stackable::Vertical);
    m_root_ui->AddChild(menubar);
    m_root_ui->AddChild(new guimp::ui::ToolsPanel);

    m_canvas = new guimp::Canvas(Size{WindowWidth, WindowHeight});
    m_current_tool = new guimp::Pencil;
}

void GameApp::OnUpdate()
{
    if (Input->IsMouseDown(MouseButton::Left))
    {
        m_current_tool->Use(Input->MousePosition(), *m_canvas);
    }
    else
    {
        m_current_tool->End();
    }

    m_canvas->Update(*this);
    m_root_ui->Update(*this);
}

void GameApp::OnRender()
{
    m_canvas->Draw(*this);
    m_root_ui->Draw(*this);
}