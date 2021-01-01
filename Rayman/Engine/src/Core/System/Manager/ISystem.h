#pragma once
#include "Core/System/Manager/SystemID.h"

#include <rttr/registration>

namespace Engine
{
    class SystemManager;

    class ISystem
    {
        RTTR_ENABLE();

    public:
        ISystem(SystemManager& a_SystemManager);
        virtual ~ISystem();
        ISystem(const ISystem&) = delete;

        //Standard Functions every system needs to implement
        virtual void Initialize() = 0;
        virtual void Update(float a_DeltaTime) = 0;
        virtual void Terminate() = 0;

    protected:
        SystemManager& m_SystemManager;

    };
}
