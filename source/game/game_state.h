#pragma once

#include "core/state.h"
#include "core/texture.h"
#include "ui/components/button.h"
#include "ui/components/grid.h"
#include "ui/components/menu.h"
#include "ui/components/stackable.h"
#include "ui/components/ui_node.h"

#include <map>

class App;

class GameState : public State
{
public:
    GameState(App& app);
    void Update(App&) override;
    void Draw(App&) override;
private:
    ui::Grid* grid{};
    ui::MenuBar* menubar{};
    ui::Menu* file{};
    ui::Button* button{};
    ui::Stackable* stackableh{};
    ui::Stackable* stackablev{};
    float acc = 0;
};