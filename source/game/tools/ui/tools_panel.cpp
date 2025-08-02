#include "tools_panel.h"
#include "core/color.h"
#include "game/tools/tool_type.h"
#include "game/ui/components/border.h"
#include "game/ui/components/button.h"
#include "game/ui/components/icon.h"
#include "game/ui/components/label.h"
#include "game/ui/components/stackable.h"
#include "game/ui/components/ui_node.h"

namespace guimp::ui
{
ToolsPanel::ToolsPanel(::ui::UiNode* parent)
    : ::ui::Border(parent)
{
    SetFill(true);
    SetColor(Colors::GRAY);
        
    auto* root = new ::ui::Stackable(::ui::Stackable::Vertical, this);
    root->AddChild(new ::ui::Label("Tools"));

    ::ui::Stackable* hor = new ::ui::Stackable(::ui::Stackable::Horizontal, root);
    ::ui::Stackable* col1 = new ::ui::Stackable(::ui::Stackable::Vertical, hor);
    ::ui::Stackable* col2 = new ::ui::Stackable(::ui::Stackable::Vertical, hor);

    auto* pencil = new ::ui::Button(new ::ui::Icon("icons/editor/pencil.png"), col1);
    pencil->OnClick([this](auto*)
        { OnChangeToolType.Emit(ToolType::Pensil); });

    auto* spray = new ::ui::Button(new ::ui::Icon("icons/editor/spray.png"), col1);
    spray->OnClick([this](auto*)
        { OnChangeToolType.Emit(ToolType::Spray); });

    auto* filler = new ::ui::Button(new ::ui::Icon("icons/editor/filler.png"), col2);
    filler->OnClick([this](auto*)
        { OnChangeToolType.Emit(ToolType::Filler); });

    auto* text = new ::ui::Button(new ::ui::Icon("icons/editor/text.png"), col2);
    text->OnClick([this](auto*)
        { OnChangeToolType.Emit(ToolType::Text); });
}
} // namespace guimp::ui