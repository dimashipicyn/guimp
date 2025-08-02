#include "core/app.h"
#include "game_state.h"
#include "constant.h"
#include "core/color.h"
#include "core/input.h"
#include "core/texture.h"
#include "ui/components/button.h"
#include "ui/components/grid.h"
#include "ui/components/icon.h"
#include "ui/components/label.h"
#include "ui/components/menu.h"
#include "ui/components/stackable.h"

GameState::GameState(App& /*app*/)
{
    // grid = new ui::Grid({2, 2}, {
    //     new ui::Button(new ui::Icon("icons/editor/00000.png")),
    //     new ui::Button(new ui::Icon("icons/editor/00001.png")),
    //     new ui::Button(new ui::Icon("icons/editor/00018.png")),
    //     new ui::Button(new ui::Icon("icons/editor/00073.png")),
    // });
    // grid->SetPos({WindowCenterW, WindowCenterH});

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
    // file->SetPos({WindowCenterW, WindowCenterH});

    auto* edit = new ui::Menu;
    edit->AddChild(new ui::Button("Undo"));
    edit->AddChild(new ui::Button("Redo"));
    edit->AddChild(new ui::Button("Copy"));
    edit->AddChild(new ui::Button("Paste"));

    menubar = new ui::MenuBar;
    // menubar->SetPos({WindowCenterW, WindowCenterH});
    menubar->Add("File", file);
    menubar->Add("Edit", edit);

    // button = new ui::Button("OK");
    // button->SetPos({WindowCenterW, WindowCenterH});

    // stackableh = new ui::Stackable(ui::Stackable::Horizontal);
    // stackableh->SetPos({WindowCenterW, WindowCenterH});
    // stackableh->AddChild(new ui::Button("OK"));
    // stackableh->AddChild(new ui::Button("GAY"));

    // stackablev = new ui::Stackable(ui::Stackable::Vertical);
    // stackablev->AddChild(new ui::Button("OK"));
    // stackablev->AddChild(new ui::Button("GAY"));
    // stackablev->AddChild(new ui::Button("!"));
    
    // stackableh->AddChild(stackablev);
    // stackableh->AddChild(new ui::Button("!"));

    // icon = new ui::Stackable(ui::Stackable::Vertical);
    // auto* h = new ui::Stackable;
    // h->AddChild(new ::ui::Icon("icons/editor/00000.png", {16,16}));
    // h->AddChild(new ::ui::Icon("icons/editor/00000.png", {16,16}));
    // icon->AddChild(h);
}

void GameState::Update(App& app)
{
    acc += app.DeltaTime * 10;

    // icon->Update(app);
    // button->Update(app);
    // grid->Update(app);
    menubar->Update(app);
    // stackableh->Update(app);
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
    // icon->Draw(app);
    // grid->Draw(app);
    menubar->Draw(app);
    // file->Draw(app);
    // button->Draw(app);
    // stackableh->Draw(app);
}
