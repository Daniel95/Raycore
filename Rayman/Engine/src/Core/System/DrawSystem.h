#pragma once

#include "Core/System/Manager/ISystem.h"

#include <CommandList.h>

#include <vector>
#include <memory>

namespace Engine
{
    class SystemManager;
    struct DrawData;

    class DrawSystem : public ISystem, public SystemRegistry<DrawSystem>
    {
    public:
        DrawSystem(SystemManager& a_SystemManager);
        ~DrawSystem();

        void Initialize() override;
        void Update(float a_DeltaTime) override;
        void Render(std::shared_ptr<CommandList> a_CommandList);
        void Terminate() override;

		void AddDrawData(const DrawData* a_DrawData);
		void RemoveDrawData(const DrawData* a_DrawData);

    private:
		std::vector<const DrawData*> m_DrawData;

		bool IsDrawDataValid(const DrawData* a_DrawData);
    };
};