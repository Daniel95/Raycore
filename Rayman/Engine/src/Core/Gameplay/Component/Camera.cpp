#include "RayCorePCH.h"

#include "Core/Gameplay/Component/Camera.h"

#include "Core/Application.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/Transform.h"

#include <DX12Application.h>
#include <Window.h>

Engine::Camera* Engine::Camera::ms_MainCamera = nullptr;

Engine::Camera::Camera()
{
	m_Data = (AlignedData*)_aligned_malloc(sizeof(AlignedData), 16);

	if (ms_MainCamera == nullptr)
	{
		ms_MainCamera = this;
	}
}

Engine::Camera::~Camera()
{
	if (ms_MainCamera == this)
	{
		ms_MainCamera = nullptr;
	}

	_aligned_free(m_Data);
}

void Engine::Camera::Init(GameObject* a_GameObject)
{
	Component::Init(a_GameObject);

	GetGameObject()->GetTransform()->SetPosition(DXS::Vector3(0, 0, -50));
	GetGameObject()->GetTransform()->SetRotation(DXS::Quaternion::Identity);

	m_Data->m_Translation = GetGameObject()->GetTransform()->GetTranslation();
	m_Data->m_Rotation = GetGameObject()->GetTransform()->GetRotation();

	LookAt(DXS::Vector3::Zero, DXS::Vector3::Down);
	SetOrthographicProjection(GetGameObject()->GetScene()->GetApplication()->GetClientWidth(), 
							  GetGameObject()->GetScene()->GetApplication()->GetClientHeight());
}

void Engine::Camera::Update(float a_DeltaTime)
{
	a_DeltaTime;

	m_Data->m_Translation = GetGameObject()->GetTransform()->GetTranslation();
	m_Data->m_Rotation = GetGameObject()->GetTransform()->GetRotation();
}

void Engine::Camera::Inspect()
{
    m_DirtyProjection = true;
    m_DirtyView = true;
}

void Engine::Camera::SetMainCamera()
{
	ms_MainCamera = this;
}

void Engine::Camera::SetBounds(const DXS::Vector2& a_Bounds)
{
	m_Bounds = a_Bounds;

	m_DirtyProjection = true;
}

void Engine::Camera::SetRenderDistance(const float& a_NearZ, const float& a_FarZ)
{
	m_NearZ = a_NearZ;
	m_FarZ = a_FarZ;

	m_DirtyProjection = true;
}

void Engine::Camera::SetOrthographicProjection(const int& a_Width, const int& a_Height)
{
	m_Width = a_Width;
	m_Height = a_Height;

	m_DirtyProjection = true;
}

DXS::Matrix Engine::Camera::GetProjectionMatrix()
{
	if (m_DirtyProjection)
	{
		UpdateProjectionMatrix();
		m_DirtyProjection = false;
	}

	return m_Data->m_ProjectionMatrix;
}

DXS::Matrix Engine::Camera::GetInverseProjectionMatrix()
{
	if (m_DirtyProjection)
	{
		UpdateProjectionMatrix();
		m_DirtyProjection = false;
	}

	return m_Data->m_InverseProjectionMatrix;
}

DXS::Matrix Engine::Camera::GetViewMatrix()
{
	if (m_DirtyView || GetGameObject()->GetTransform()->IsDirty())
	{
		UpdateViewMatrix();
		m_DirtyView = false;
	}

	return m_Data->m_ViewMatrix;
}

DXS::Matrix Engine::Camera::GetInverseViewMatrix()
{
	if (m_DirtyView || GetGameObject()->GetTransform()->IsDirty())
	{
		UpdateViewMatrix();
		m_DirtyView = false;
	}

	return m_Data->m_InverseViewMatrix;
}

void Engine::Camera::LookAt(const DXS::Vector3& a_Target, const DXS::Vector3& a_Up)
{
	m_Data->m_ViewMatrix = DirectX::XMMatrixLookAtLH(GetGameObject()->GetTransform()->GetPosition(), a_Target, a_Up);

	GetGameObject()->GetTransform()->SetRotation(DirectX::XMQuaternionRotationMatrix(DirectX::XMMatrixTranspose(m_Data->m_ViewMatrix)));
	m_Data->m_Rotation = GetGameObject()->GetTransform()->GetRotation();

	m_DirtyView = true;
}

Engine::Camera& Engine::Camera::GetMainCamera()
{
    if (ms_MainCamera == nullptr)
    {
        ms_MainCamera;
        return *ms_MainCamera;
    }

	_ASSERT(ms_MainCamera != nullptr); //Always load/set the main camera fore accessing it!
	_ASSERT(ms_MainCamera->GetGameObject() != nullptr); //Check if camera is initialized.

	return *ms_MainCamera;
}

bool Engine::Camera::HasMainCamera()
{
	return ms_MainCamera != nullptr;
}

void Engine::Camera::OnEnable()
{
    if (ms_MainCamera == nullptr)
    {
        ms_MainCamera = this;
    }
}

void Engine::Camera::OnDisable()
{
    if (ms_MainCamera == this)
    {
        ms_MainCamera = nullptr;
    }
}

void Engine::Camera::UpdateProjectionMatrix()
{
	float viewWidth, viewHeight, orthographicSize;
	float aspectRatio = static_cast<float>(m_Width) / static_cast<float>(m_Height);
	float targetAspectRatio = m_Bounds.x / m_Bounds.y;

	if (targetAspectRatio < aspectRatio)
	{
		orthographicSize = m_Bounds.y / 2.f;
	}
	else
	{
		float dif = targetAspectRatio / aspectRatio;
		orthographicSize = m_Bounds.y / 2.f * dif;
	}

	viewHeight = 2.f * orthographicSize;
	viewWidth = viewHeight * aspectRatio;

	m_Data->m_ProjectionMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, m_NearZ, m_FarZ);
	m_Data->m_InverseProjectionMatrix = DirectX::XMMatrixInverse(nullptr, m_Data->m_ProjectionMatrix);
}

void Engine::Camera::UpdateViewMatrix()
{
	m_Data->m_ViewMatrix = GetGameObject()->GetTransform()->GetTranslationMatrix() * GetGameObject()->GetTransform()->GetRotationMatrix();
	m_Data->m_InverseViewMatrix = XMMatrixInverse(nullptr, m_Data->m_ViewMatrix);
}

RTTR_REGISTRATION
{
	rttr::registration::class_<Engine::Camera>("Camera")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("Bounds", &Engine::Camera::m_Bounds)
		.property("NearZ", &Engine::Camera::m_NearZ)
		.property("FarZ", &Engine::Camera::m_FarZ);
}