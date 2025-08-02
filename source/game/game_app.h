#pragma once

#include "core/app.h"
#include "game/ui/components/ui_node.h"
#include "tools/tool.h"

class GameApp : public App
{
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;

private:
    ui::UiNode* m_root_ui{};

    guimp::Canvas* m_canvas{};
    guimp::Tool* m_current_tool{};
};