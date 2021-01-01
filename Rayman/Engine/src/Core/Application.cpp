#include "RayCorePCH.h"

#include "Core/Application.h"

#include "Core/Gameplay/Component/Camera.h"
#include "Core/System/DrawSystem.h"
#include "Core/System/EventSystem.h"
#include "Core/System/GameSystem.h"
#include "Core/System/ImGuiSystem.h"
#include "Core/System/ResourceSystem.h"
#include "Core/System/SceneSystem.h"
#include "Core/System/SoundSystem.h"
#include "Core/Gameplay/Component/SpriteRenderer.h"
#include "Core/System/InputSystem.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/System/Resource/Material.h"
#include "Core/System/Resource/Mesh.h"
#include "Core/System/Resource/Texture.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Utilities/Log.h"
#include "Core/Utilities/Math/DX12Matrix.h"
#include "Core/Utilities/Math/SimpleMath.h"
#include "Core/Utilities/Math/MatrixUtils.h"
#include "Graphics/DX12Material.h"
#include "Graphics/RootParameters.h"

#include <imgui.h>

namespace Engine
{
    Application::Application() : DX12Application(L"Rayman DX12", 1280, 720, false),
		m_SystemManager(*new SystemManager()),
		m_ScissorRect(CD3DX12_RECT(0, 0, LONG_MAX, LONG_MAX)), 
		m_Viewport(CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(1280), static_cast<float>(720))),
		m_Width(0),
		m_Height(0)
    {
    #ifdef EDITOR
        m_EditorMode = true;
    #endif // EDITOR

        m_SystemManager.CreateSystem<ResourceSystem>();
        m_SystemManager.CreateSystem<SoundSystem>();
        m_SystemManager.CreateSystem<SceneSystem>(*this);
        m_SystemManager.CreateSystem<ImGuiSystem>();
        m_SystemManager.CreateSystem<EventSystem>();
        m_SystemManager.CreateSystem<InputSystem>();
        m_SystemManager.CreateSystem<DrawSystem>();
        m_SystemManager.CreateSystem<GameSystem>();
    }

    Application::~Application()
    {
    }

	int Application::RunSFML()
	{
		LOG_ENGINE_ERROR("This should only run in SFML mode!");
        _ASSERT(false);

		return 0;
    }

    SystemManager* Application::GetSystemManager()
    {
        return &m_SystemManager;
    }

	bool Application::LoadContent()
	{
		m_SystemManager.InitializeSystems();

		//Test fix for loading textures.
		CoInitialize(nullptr);

		auto device = DX12Graphics::Get().GetDevice();
		auto commandQueue = DX12Graphics::Get().GetCommandQueue(D3D12_COMMAND_LIST_TYPE_COPY);
		auto commandList = commandQueue->GetCommandList();

		auto& rs = GetSystemManager()->GetSystem<ResourceSystem>();

		{
			// Create/Load default texture
			rs.LoadResource<Texture>(ENGINE_TEXTURES_PATH + "DefaultTex.png");
		}

		{
			// Create/Load default material
			Material* m = rs.LoadResource<Material>("DefaultMat");
			m->m_DX12Material = DX12Material::UnlitWhite;
		}

		{
			// Create/Load default meshes
			Mesh* m = rs.LoadResource<Mesh>("CubeMesh");
			m->m_DX12Mesh = DX12Mesh::CreateCube(*commandList);
		}

		{
			// Create/Load default meshes
			Mesh* m = rs.LoadResource<Mesh>("PlaneMesh");
			m->m_DX12Mesh = DX12Mesh::CreatePlane(*commandList);
		}

		// Create a root signature.
		D3D12_FEATURE_DATA_ROOT_SIGNATURE featureData = {};
		featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;

		if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &featureData, sizeof(featureData))))
		{
			featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
		}

		// Allow input layout and deny unnecessary access to certain pipeline stages.
		D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;

		CD3DX12_DESCRIPTOR_RANGE1 descriptorRage(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 2);

		CD3DX12_ROOT_PARAMETER1 rootParameters[RootParameters::NumRootParameters];
		rootParameters[RootParameters::MatricesCB].InitAsConstantBufferView(0, 0, D3D12_ROOT_DESCRIPTOR_FLAG_NONE, D3D12_SHADER_VISIBILITY_VERTEX);
		rootParameters[RootParameters::MaterialCB].InitAsConstantBufferView(0, 1, D3D12_ROOT_DESCRIPTOR_FLAG_NONE, D3D12_SHADER_VISIBILITY_PIXEL);
		rootParameters[RootParameters::LightPropertiesCB].InitAsConstants(sizeof(LightProperties) / 4, 1, 0, D3D12_SHADER_VISIBILITY_PIXEL);
		rootParameters[RootParameters::PointLights].InitAsShaderResourceView(0, 0, D3D12_ROOT_DESCRIPTOR_FLAG_NONE, D3D12_SHADER_VISIBILITY_PIXEL);
		rootParameters[RootParameters::SpotLights].InitAsShaderResourceView(1, 0, D3D12_ROOT_DESCRIPTOR_FLAG_NONE, D3D12_SHADER_VISIBILITY_PIXEL);
		rootParameters[RootParameters::Textures].InitAsDescriptorTable(1, &descriptorRage, D3D12_SHADER_VISIBILITY_PIXEL);

		CD3DX12_STATIC_SAMPLER_DESC linearRepeatSampler(0, D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR);
		CD3DX12_STATIC_SAMPLER_DESC anisotropicSampler(0, D3D12_FILTER_ANISOTROPIC);

		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDescription;
		rootSignatureDescription.Init_1_1(RootParameters::NumRootParameters, rootParameters, 1, &linearRepeatSampler, rootSignatureFlags);

		m_RootSignature.SetRootSignatureDesc(rootSignatureDescription.Desc_1_1, featureData.HighestVersion);

		// Setup the pipeline state.
		struct PipelineStateStream
		{
			CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;
			CD3DX12_PIPELINE_STATE_STREAM_INPUT_LAYOUT InputLayout;
			CD3DX12_PIPELINE_STATE_STREAM_PRIMITIVE_TOPOLOGY PrimitiveTopologyType;
			CD3DX12_PIPELINE_STATE_STREAM_VS VS;
			CD3DX12_PIPELINE_STATE_STREAM_PS PS;
			CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL_FORMAT DSVFormat;
			CD3DX12_PIPELINE_STATE_STREAM_RENDER_TARGET_FORMATS RTVFormats;
			CD3DX12_PIPELINE_STATE_STREAM_SAMPLE_DESC SampleDesc;
			CD3DX12_PIPELINE_STATE_STREAM_BLEND_DESC BlendDesc;
			CD3DX12_PIPELINE_STATE_STREAM_RASTERIZER Rast;
		} pipelineStateStream;

		// sRGB formats provide free gamma correction!
		DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT;

		// Check the best multisample quality level that can be used for the given back buffer format.
		DXGI_SAMPLE_DESC sampleDesc = DX12Graphics::Get().GetMultisampleQualityLevels(backBufferFormat, D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT);

		D3D12_RT_FORMAT_ARRAY rtvFormats = {};
		rtvFormats.NumRenderTargets = 1;
		rtvFormats.RTFormats[0] = backBufferFormat;

		pipelineStateStream.pRootSignature = m_RootSignature.GetRootSignature().Get();
		pipelineStateStream.InputLayout = { VertexPositionNormalTexture::InputElements, VertexPositionNormalTexture::InputElementCount };
		pipelineStateStream.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		pipelineStateStream.VS = CD3DX12_SHADER_BYTECODE(VertexShader, sizeof(VertexShader));
		pipelineStateStream.PS = CD3DX12_SHADER_BYTECODE(PixelShader, sizeof(PixelShader));
		pipelineStateStream.DSVFormat = depthBufferFormat;
		pipelineStateStream.RTVFormats = rtvFormats;
		pipelineStateStream.SampleDesc = sampleDesc;

		//Setup blending.
		{
			CD3DX12_BLEND_DESC& blendDesc = pipelineStateStream.BlendDesc;
			blendDesc.AlphaToCoverageEnable = true;
			blendDesc.IndependentBlendEnable = false;
			blendDesc.RenderTarget[0].BlendEnable = TRUE;
			blendDesc.RenderTarget[0].LogicOpEnable = FALSE;
			blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		}

		//Setup rasterizer.
		{
			D3D12_RASTERIZER_DESC& desc = pipelineStateStream.Rast;
			desc.FillMode = D3D12_FILL_MODE_SOLID;
			desc.CullMode = D3D12_CULL_MODE_NONE;
			desc.FrontCounterClockwise = FALSE;
			desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
			desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			desc.DepthClipEnable = true;
			desc.MultisampleEnable = FALSE;
			desc.AntialiasedLineEnable = TRUE;
			desc.ForcedSampleCount = 0;
			desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
		}

		D3D12_PIPELINE_STATE_STREAM_DESC pipelineStateStreamDesc = { sizeof(PipelineStateStream), &pipelineStateStream };
		ThrowIfFailed(device->CreatePipelineState(&pipelineStateStreamDesc, IID_PPV_ARGS(&m_PipelineState)));

		// Create an off-screen render target with a single color buffer and a depth buffer.
		auto colorDesc = CD3DX12_RESOURCE_DESC::Tex2D(backBufferFormat,	m_Width, m_Height, 1, 1, sampleDesc.Count, sampleDesc.Quality, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);
		D3D12_CLEAR_VALUE colorClearValue;
		colorClearValue.Format = colorDesc.Format;
		colorClearValue.Color[0] = 0.58f;
		colorClearValue.Color[1] = 0.83f;
		colorClearValue.Color[2] = 0.95f;
		colorClearValue.Color[3] = 1.0f;

		DX12Texture colorTexture = DX12Texture(colorDesc, &colorClearValue,	TextureUsage::RenderTarget,	L"Color Render Target");

		// Create a depth buffer.
		auto depthDesc = CD3DX12_RESOURCE_DESC::Tex2D(depthBufferFormat, m_Width, m_Height,	1, 1, sampleDesc.Count, sampleDesc.Quality,	D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
		D3D12_CLEAR_VALUE depthClearValue;
		depthClearValue.Format = depthDesc.Format;
		depthClearValue.DepthStencil = { 1.0f, 0 };

		DX12Texture depthTexture = DX12Texture(depthDesc, &depthClearValue,	TextureUsage::Depth, L"Depth Render Target");

		//Attach the textures to the render target.
		m_RenderTarget.AttachTexture(AttachmentPoint::Color0, colorTexture);
		m_RenderTarget.AttachTexture(AttachmentPoint::DepthStencil, depthTexture);

		auto fenceValue = commandQueue->ExecuteCommandList(commandList);
		commandQueue->WaitForFenceValue(fenceValue);
	
		return true;
	}

	void Application::UnloadContent()
	{
	}

	void Application::OnStart()
	{
    #ifdef EDITOR
        Engine::Scene* scene = new Engine::Scene(0, TEST_LEVEL);
        scene->SetApplication(*this);
        scene->CreateCamera();

        {
            Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(15, 0), DXS::Vector2(30, 2));
            gameObject.AddComponent<SpriteRenderer>();
            gameObject.GetComponent<SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
            gameObject.AddComponent<BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
        }

        scene->Update(0.016f);
        scene->Save(GAME_SCENE_PATH, TEST_LEVEL);

        delete scene;

        GetSystemManager()->GetSystem<Engine::SceneSystem>().LoadScene(TEST_LEVEL);
    #endif // EDITOR
	}

	bool Application::IsEditorMode() const
	{
		return m_EditorMode;
	}

	void Application::OnFixedUpdate(FixedUpdateEventArgs& a_FixedUpdateEventArgs)
	{
		static uint64_t frameCount = 0;
		static double totalTime = 0.0;

		DX12Application::OnFixedUpdate(a_FixedUpdateEventArgs);

		totalTime += a_FixedUpdateEventArgs.FixedDeltaTime;
		frameCount++;

		if (totalTime > 10.0)
		{
			double fps = frameCount / totalTime;

			LOG_ENGINE_INFO("FFPS: " + std::to_string(fps));

			frameCount = 0;
			totalTime = 0.0;
		}

		m_SystemManager.GetSystem<SceneSystem>().FixedUpdate(a_FixedUpdateEventArgs.FixedDeltaTime);
	}

	void Application::OnUpdate(UpdateEventArgs& a_UpdateEventArgs)
	{
		static uint64_t frameCount = 0;
		static double totalTime = 0.0;

		DX12Application::OnUpdate(a_UpdateEventArgs);

		totalTime += a_UpdateEventArgs.DeltaTime;
		frameCount++;

		if (totalTime > 1.0)
		{
			double fps = frameCount / totalTime;

			LOG_ENGINE_INFO("FPS: " + std::to_string(fps));

			frameCount = 0;
			totalTime = 0.0;
		}

		m_SystemManager.UpdateSystems(static_cast<float>(a_UpdateEventArgs.DeltaTime));
		m_SystemManager.GetSystem<ResourceSystem>().LateUpdate();
	}

	void Application::OnRender(RenderEventArgs& a_RenderEventArgs)
	{
		DX12Application::OnRender(a_RenderEventArgs);

		auto commandQueue = DX12Graphics::Get().GetCommandQueue(D3D12_COMMAND_LIST_TYPE_DIRECT);
		auto commandList = commandQueue->GetCommandList();

		//Clear the render targets.
		{
			FLOAT clearColor[] = { 0.58f, 0.83f, 0.95f, 1.0f };

			commandList->ClearTexture(m_RenderTarget.GetTexture(AttachmentPoint::Color0), clearColor);
			commandList->ClearDepthStencilTexture(m_RenderTarget.GetTexture(AttachmentPoint::DepthStencil), D3D12_CLEAR_FLAG_DEPTH);
		}

		commandList->SetPipelineState(m_PipelineState);
		commandList->SetGraphicsRootSignature(m_RootSignature);

		commandList->SetViewport(m_Viewport);
		commandList->SetScissorRect(m_ScissorRect);

		commandList->SetRenderTarget(m_RenderTarget);
        m_SystemManager.GetSystem<DrawSystem>().Render(commandList);
		commandQueue->ExecuteCommandList(commandList);

		//Render GUI.
		m_SystemManager.GetSystem<ImGuiSystem>().RenderEditorWindows();

		//Present
		m_pWindow->Present(m_RenderTarget.GetTexture(AttachmentPoint::Color0));
	}

	void Application::OnResize(ResizeEventArgs& a_ResizeEventArgs)
	{
		DX12Application::OnResize(a_ResizeEventArgs);

		if (m_Width != a_ResizeEventArgs.Width || m_Height != a_ResizeEventArgs.Height)
		{
			m_Width = std::max(1, a_ResizeEventArgs.Width);
			m_Height = std::max(1, a_ResizeEventArgs.Height);

			if (Camera::HasMainCamera())
			{
				Camera::GetMainCamera().SetOrthographicProjection(m_Width, m_Height);
			}

			m_Viewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height));
			m_RenderTarget.Resize(m_Width, m_Height);
		}
	}

    void Application::OnKeyPressed(KeyEventArgs& a_KeyEventArgs)
    {
        if (!ImGui::GetIO().WantCaptureKeyboard)
        {
            m_SystemManager.GetSystem<InputSystem>().OnKeyPressed(a_KeyEventArgs);
        }
    }

    void Application::OnKeyReleased(KeyEventArgs& a_KeyEventArgs)
    {
        if (!ImGui::GetIO().WantCaptureKeyboard)
        {
            m_SystemManager.GetSystem<InputSystem>().OnKeyReleased(a_KeyEventArgs);
        }
    }

    void Application::OnMouseMoved(MouseMotionEventArgs& a_MouseMotionEventArgs)
    {
        m_SystemManager.GetSystem<InputSystem>().OnMouseMoved(a_MouseMotionEventArgs);
    }

    void Application::OnMouseButtonPressed(MouseButtonEventArgs& a_MouseButtonEventArgs)
    {
        m_SystemManager.GetSystem<InputSystem>().OnMouseButtonPressed(a_MouseButtonEventArgs);
    }

    void Application::OnMouseButtonReleased(MouseButtonEventArgs& a_MouseButtonEventArgs)
    {
        m_SystemManager.GetSystem<InputSystem>().OnMouseButtonReleased(a_MouseButtonEventArgs);
    }

    void Application::OnMouseWheel(MouseWheelEventArgs& a_MouseWheelEventArgs)
    {
        m_SystemManager.GetSystem<InputSystem>().OnMouseWheel(a_MouseWheelEventArgs);
    }
}