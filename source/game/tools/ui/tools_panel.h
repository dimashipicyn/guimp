#pragma once

#include "game/ui/components/border.h"
#include "game/tools/tool_type.h"
#include "game/signal.h"

namespace guimp::ui
{
class ToolsPanel : public ::ui::Border
{
public:
    ToolsPanel(::ui::UiNode* parent = nullptr);
    Signal<ToolType> OnChangeToolType;
private:
};
} // namespace guimp::ui