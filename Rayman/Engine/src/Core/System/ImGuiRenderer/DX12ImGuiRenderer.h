#pragma once
#include "Core/System/ImGuiRenderer/IImGuiRenderer.h"

namespace Engine
{
    class DX12ImGuiRenderer : public IImGuiRenderer
    {
    public:
        DX12ImGuiRenderer();
        ~DX12ImGuiRenderer();

        void Init() override;
        void Update() override;
        void Render() override;
        void Terminate() override;

    };
}
