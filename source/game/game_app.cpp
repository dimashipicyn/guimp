#include "game_app.h"
#include "core/provider.h"
#include "core/state.h"
#include "game_state.h"
#include "state_id.h"

void GameApp::OnInit()
{
    StateManager->Register<GameState>(StateId::Run, *this);
    StateManager->Change(StateId::Run);
}

void GameApp::OnUpdate()
{
}

void GameApp::OnRender()
{
}