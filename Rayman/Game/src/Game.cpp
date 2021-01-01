#include "Game.h"
#include "SceneLibrary.h"
#include "Core/Engine.h"
#include "Core/System/Manager/SystemManager.h"

Engine::Application* Engine::CreateApplication()
{
	return new Game();
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::OnStart()
{
	Application::OnStart();

    if (!m_EditorMode)
    {
        GetSystemManager()->GetSystem<Engine::SceneSystem>().LoadScene(LEVEL_1_NAME);
    }
}
