#include "RayCorePCH.h"

#include "Core/Gameplay/Component/SpriteRenderer.h"

#include "Core/Gameplay/Component/Transform.h"
#include "Core/Gameplay/GameObject.h"

#include "Core/Utilities/Log.h"
#include "Core/Application.h"

#include "Core/System/Manager/SystemManager.h"
#include "Core/System/DrawSystem.h"
#include "Core/System/Draw/DrawData.h"
#include "Core/System/Scene/Scene.h"
#include "Core/System/ResourceSystem.h"

#include "Core/System/Resource/Material.h"
#include "Graphics/DX12Material.h"

#include "Core/System/Resource/Texture.h"

#include "Core\System\Resource\Mesh.h"
#include "Core\Gameplay\Component\Camera.h"

namespace Engine 
{
    SpriteRenderer::SpriteRenderer()
    {
		//Create draw data.
		m_DrawData = new DrawData();
		//Set default texture.
		m_TextureName = ENGINE_TEXTURES_PATH + "DefaultTex.png";
	}

    SpriteRenderer::~SpriteRenderer()
    {
		GetGameObject()->GetSystemManager()->GetSystem<DrawSystem>().RemoveDrawData(m_DrawData);
		delete m_DrawData;
    }

    void SpriteRenderer::Init(GameObject* a_GameObject)
    {
        Component::Init(a_GameObject);

		ResourceSystem& rs = GetGameObject()->GetSystemManager()->GetSystem<ResourceSystem>();

		m_DrawData->m_Mesh = rs.LoadResource<Mesh>("PlaneMesh");
		m_DrawData->m_Material = rs.LoadResource<Material>("DefaultMat");

		if (Camera::HasMainCamera())
		{
			DXS::Matrix viewMat = Camera::GetMainCamera().GetViewMatrix();
			DXS::Matrix viewProjectionMat = viewMat * Camera::GetMainCamera().GetProjectionMatrix();
			MatrixUtils::ComputeMatrices(GetGameObject()->GetTransform()->GetModelMatrix(), viewMat, viewProjectionMat, *m_DrawData->m_Maticies);
		}

		SetTexture(m_TextureName);
		SetLayer(m_Layer);
    }

    void SpriteRenderer::Update(float a_DeltaTime)
    {
        a_DeltaTime;

		if (Camera::HasMainCamera())
		{
			DXS::Matrix viewMat = Camera::GetMainCamera().GetViewMatrix();
			DXS::Matrix viewProjectionMat = viewMat * Camera::GetMainCamera().GetProjectionMatrix();
			MatrixUtils::ComputeMatrices(GetGameObject()->GetTransform()->GetModelMatrix(), viewMat, viewProjectionMat, *m_DrawData->m_Maticies);
		}
    }

	void SpriteRenderer::OnEnable()
	{
		GetGameObject()->GetSystemManager()->GetSystem<DrawSystem>().AddDrawData(m_DrawData);
	}

	void SpriteRenderer::OnDisable()
	{
		GetGameObject()->GetSystemManager()->GetSystem<DrawSystem>().RemoveDrawData(m_DrawData);
	}

    void SpriteRenderer::Inspect()
    {
        SetLayer(m_Layer);
	}

	void SpriteRenderer::SetLayer(int a_Layer)
	{
		m_Layer = a_Layer;

		//Set position.
		DXS::Vector3 p = GetGameObject()->GetTransform()->GetPosition();
		p.z = static_cast<float>(a_Layer);
		GetGameObject()->GetTransform()->SetPosition(p);
	}

	int SpriteRenderer::GetLayer()
	{
		return m_Layer;
	}

	void SpriteRenderer::SetMaterial(Material& a_Material)
	{
		m_DrawData->m_Material = &a_Material;
	}

	void SpriteRenderer::SetTexture(const std::string& a_TexturePath)
	{
		Texture* t = GetGameObject()->GetSystemManager()->GetSystem<ResourceSystem>().LoadResource<Texture>(a_TexturePath);

		if (t != nullptr)
		{
			//if (t->m_DX12Texture.IsValid())
			//{
				m_TextureName = a_TexturePath;
				m_DrawData->m_Texture = t;
			//}
		}
	}
}

RTTR_REGISTRATION
{
	rttr::registration::class_<Engine::SpriteRenderer>("SpriteRenderer")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("TextureName", &Engine::SpriteRenderer::m_TextureName)
		.property("Layer", &Engine::SpriteRenderer::m_Layer);
}