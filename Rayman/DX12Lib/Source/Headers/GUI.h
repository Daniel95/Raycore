#pragma once

#include <d3dx12.h>
#include <wrl.h>
#include <memory>
#include <imgui.h>

class CommandList;
class DX12Texture;
class RenderTarget;
class RootSignature;
class Window;

class GUI
{
public:
	GUI();
	virtual ~GUI();

	//Initialize the ImGui context.
	virtual bool Initialize(std::shared_ptr<Window> a_Window);

	//Begin a new frame.
	virtual void Update();
	virtual void Render(std::shared_ptr<CommandList> a_CommandList, const RenderTarget& a_RenderTarget);

	//Destroy the ImGui context.
	virtual void Destroy();

protected:

private:
	ImGuiContext* m_pImGuiCtx;
	std::unique_ptr<DX12Texture> m_FontTexture;
	std::unique_ptr<RootSignature> m_RootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_PipelineState;
	std::shared_ptr<Window> m_Window;
};