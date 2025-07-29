#include "core/app.h"
#include "game_state.h"
#include "constant.h"
#include "core/color.h"
#include "core/input.h"
#include "core/texture.h"
#include "ui/components/button.h"
#include "ui/components/grid.h"
#include "ui/components/icon.h"
#include "ui/components/menu.h"
#include "ui/components/stackable.h"

GameState::GameState(App& /*app*/)
{
    grid = new ui::Grid({2, 2}, {
        new ui::Button(new ui::Icon("icons/editor/00000.png")),
        new ui::Button(new ui::Icon("icons/editor/00001.png")),
        new ui::Button(new ui::Icon("icons/editor/00018.png")),
        new ui::Button(new ui::Icon("icons/editor/00073.png")),
    });
    // grid->SetPos({WindowCenterW, WindowCenterH});

    file = new ui::Menu("File", {
        new ui::Grid({2, 1}, {
            new ui::Button("Open"),
            new ui::Icon("icons/editor/00000.png", {16,16})
        }),
        new ui::Button("Save"),
        new ui::Button("Exit")
    });
    // file->SetPos({WindowCenterW, WindowCenterH});

    auto* edit = new ui::Menu("Edit");
    edit->AddChild(new ui::Button("Undo"));
    edit->AddChild(new ui::Button("Redo"));
    edit->AddChild(new ui::Button("Copy"));
    edit->AddChild(new ui::Button("Paste"));

    menubar = new ui::MenuBar;
    // menubar->SetPos({WindowCenterW, WindowCenterH});
    menubar->Add(file);
    menubar->Add(edit);

    button = new ui::Button("OK");
    // button->SetPos({WindowCenterW, WindowCenterH});

    stackableh = new ui::Stackable(ui::Stackable::Horizontal);
    stackableh->SetPos({WindowCenterW, WindowCenterH});
    stackableh->AddChild(new ui::Button("OK"));
    stackableh->AddChild(new ui::Button("GAY"));

    stackablev = new ui::Stackable(ui::Stackable::Vertical);
    stackablev->AddChild(new ui::Button("OK"));
    stackablev->AddChild(new ui::Button("GAY"));
    stackablev->AddChild(new ui::Button("!"));
    
    stackableh->AddChild(stackablev);
    stackableh->AddChild(new ui::Button("!"));
}

void GameState::Update(App& app)
{
    acc += app.DeltaTime * 10;

    // button->Update(app);
    // grid->Update(app);
    menubar->Update(app);
    stackableh->Update(app);
    // file->Update(app);
    // if (acc >= 1.0f)
    // {
    //     // button->SetPos(button->GetPos() + Point { (int)acc, (int)acc });
    //     grid->SetPos(grid->GetPos() + Point { (int)acc, (int)acc });
    //     acc -= (int)acc;
    // }
}

void GameState::Draw(App& app)
{
    // grid->Draw(app);
    menubar->Draw(app);
    // file->Draw(app);
    // button->Draw(app);
    stackableh->Draw(app);
}
