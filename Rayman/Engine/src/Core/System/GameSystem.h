#pragma once
#include "Core/System/Manager/ISystem.h"

namespace Engine
{
    class GameSystem : public ISystem, public SystemRegistry<GameSystem>
    {
    public:
        GameSystem(SystemManager& a_SystemManager);
        ~GameSystem();

        void Initialize();
        void Update(float a_DeltaTime);
        void Terminate();
        int GetLives();
        void SetLives(int a_Lives);
    private:
        int m_Lives = 3;

    };
}
