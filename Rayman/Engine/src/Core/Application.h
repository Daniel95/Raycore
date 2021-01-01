#pragma once

#include <vector>
#include <chrono>

#include <DX12LibPCH.h>
#include <DX12Application.h>
#include <Window.h>
#include <RenderTarget.h>
#include <RootSignature.h>
#include <VertexBuffer.h>
#include <DirectXMath.h>

#include "Graphics/Light.h"

namespace sf 
{
	class RenderWindow;
}

namespace Engine
{
    class GameWindow;
    class SceneSystem;
    class SystemManager;
    class SFMLImGuiRenderer;

    using namespace std::chrono_literals;
    constexpr std::chrono::nanoseconds timestepNano(16ms);

	class Application : public DX12Application
	{
	public:
		Application();
		virtual ~Application();

        int RunSFML();
        SystemManager* GetSystemManager();

		virtual bool LoadContent() override;
		virtual void UnloadContent() override;
		virtual void OnStart() override;

		bool IsEditorMode() const;

	protected:
		virtual void OnFixedUpdate(FixedUpdateEventArgs& a_FixedUpdateEventArgs) override;
		virtual void OnUpdate(UpdateEventArgs& a_UpdateEventArgs) override;
		virtual void OnRender(RenderEventArgs& a_RenderEventArgs) override;
		virtual void OnResize(ResizeEventArgs& a_ResizeEventArgs) override;
        virtual void OnKeyPressed(KeyEventArgs& a_KeyEventArgs) override;
        virtual void OnKeyReleased(KeyEventArgs& a_KeyEventArgs) override;
        virtual void OnMouseMoved(MouseMotionEventArgs& a_MouseMotionEventArgs) override;
        virtual void OnMouseButtonPressed(MouseButtonEventArgs& a_MouseButtonEventArgs) override;
        virtual void OnMouseButtonReleased(MouseButtonEventArgs& a_MouseButtonEventArgs) override;
        virtual void OnMouseWheel(MouseWheelEventArgs& a_MouseWheelEventArgs) override;

    protected:
        bool m_EditorMode = false;

	private:
        SystemManager& m_SystemManager;
        std::chrono::nanoseconds m_Lag = std::chrono::nanoseconds(0ns);//(std::chrono::nanoseconds)0;
        std::chrono::time_point<std::chrono::steady_clock> m_TimeStart = std::chrono::high_resolution_clock::now();
        SFMLImGuiRenderer* sfmlImGuiRenderer = nullptr;

		//DX12-------------------------------------------------------------
		RenderTarget m_RenderTarget;
		RootSignature m_RootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_PipelineState;

		//Width and height used for the buffers and window resize.
		int m_Width;
		int m_Height;

		D3D12_VIEWPORT m_Viewport;
		D3D12_RECT m_ScissorRect;
		//DX12-------------------------------------------------------------
	};

	// To be defined in client.
	Application* CreateApplication();
}