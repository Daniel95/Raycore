#pragma once
#include "Core/System/Manager/ISystem.h"

#include "Core/Utilities/Inspectable.h"

#include <imgui.h>
#include <unordered_map>

namespace Engine
{
    class IImGuiRenderer;
    class IImGuiWindow;
    class SystemManager;

    class ImGuiSystem : public ISystem, public Inspectable, public SystemRegistry<ImGuiSystem>
    {
        RTTR_ENABLE(ISystem, Inspectable);

    public:
        ImGuiSystem(SystemManager& a_SystemManager);
        ~ImGuiSystem();

        void Initialize() override;
        void Update(float a_DeltaTime) override;
        void Terminate() override;

        void Inspect() override;

        // void RegisterEditorWindow(Inspectable* a_InspectableWindow);
        void RenderEditorWindows();

    private:
        void CreateDockspace();

    private:
        IImGuiRenderer* m_ImGuiRenderer;
        bool m_IsEnabled = true;

    };
}
