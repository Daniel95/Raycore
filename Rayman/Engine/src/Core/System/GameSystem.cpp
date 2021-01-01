#include "RayCorePCH.h"

#include "Core/System/Manager/SystemManager.h"
#include "Core/System/GameSystem.h"
#include "Core/Utilities/Log.h"

namespace Engine
{
    GameSystem::GameSystem(SystemManager& a_SystemManager)
        : ISystem(a_SystemManager)
    {
    }

    GameSystem::~GameSystem()
    {
        //LOG_ENGINE_WARN("Game System terminated!");
    }

    void GameSystem::Initialize()
    {
        m_Lives;
    }

    void GameSystem::Update(float a_DeltaTime)
    {
        a_DeltaTime;
    }

    void GameSystem::Terminate()
    {

    }
    int GameSystem::GetLives()
    {
        return m_Lives;
    }
    void GameSystem::SetLives(int a_Lives)
    {
        m_Lives = a_Lives;
    }
}
