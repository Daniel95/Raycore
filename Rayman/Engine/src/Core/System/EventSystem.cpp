#include "RayCorePCH.h"

#include "EventSystem.h"
#include "Core/Utilities/Log.h"
#include "Core/System/Manager/SystemManager.h"

namespace Engine
{
    EventSystem::EventSystem(SystemManager& a_SystemManager)
        : ISystem(a_SystemManager)
    {
    }

    EventSystem::~EventSystem()
    {
    }

    void EventSystem::Initialize()
    {
    }

    void EventSystem::Update(float a_DeltaTime)
    {
        a_DeltaTime;
    }

    void EventSystem::Terminate()
    {
    }
}