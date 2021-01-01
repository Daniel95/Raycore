#include "RayCorePCH.h"

#include "Core/System/Manager/SystemManager.h"

#include "Core/System/ImGuiSystem.h" // For the friendship
#include "Core/System/Manager/ISystem.h"

namespace Engine
{
    SystemManager::SystemManager()
    {

    }

    SystemManager::~SystemManager()
    {
        for (auto itr = m_Systems.begin(); itr != m_Systems.end(); itr++)
        {
            ISystem* system = itr->second;
            system->Terminate();
            delete system;
        }
    }

    std::vector<ISystem*> SystemManager::GetAllSystems()
    {
        std::vector<ISystem*> systemList = std::vector<ISystem*>();

        for (auto itr = m_Systems.begin(); itr != m_Systems.end(); ++itr)
        {
            systemList.push_back(itr->second);
        }

        return systemList;
    }

    void SystemManager::InitializeSystems()
    {
        for (auto itr = m_Systems.begin(); itr != m_Systems.end(); itr++)
        {
            itr->second->Initialize();
        }
    }

    void SystemManager::UpdateSystems(float a_DeltaTime)
    {
        for (auto itr = m_Systems.begin(); itr != m_Systems.end(); itr++)
        {
            itr->second->Update(a_DeltaTime);
        }
    }
}
