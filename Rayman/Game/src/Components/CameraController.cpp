#include "CameraController.h"

#include "Core/Gameplay/Component/Camera.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/Transform.h"
#include "Core/System/Scene/Scene.h"

#include "Components/Player.h"

CameraController::CameraController()
{

}

CameraController::~CameraController()
{

}

void CameraController::Init(GameObject* a_GameObject)
{
	Component::Init(a_GameObject);
}

void CameraController::Update(float a_DeltaTime)
{
	if (!m_HasSetPlayer)
	{
		for (GameObject* g : GetGameObject()->GetScene()->GetGameObjects())
		{
			if (g != nullptr)
			{
				if (g->GetComponent<Player>() != nullptr)
				{
					SetTarget(&g->GetTransform()->GetPosition());
					m_HasSetPlayer = true;
					break;
				}
			}
		}
	}

	if (m_Target != nullptr && Camera::HasMainCamera())
	{
		DXS::Vector2 targetPos = DXS::Vector2(-m_Target->x, -m_Target->y);

		if (m_LastPos.x < m_Target->x - (m_DeadZone * a_DeltaTime))
		{
			targetPos.x -= m_LookAheadX;
		}
		else if (m_LastPos.x > m_Target->x + (m_DeadZone * a_DeltaTime))
		{
			targetPos.x += m_LookAheadX;
		}

		if (m_LastPos.y < m_Target->y - (m_DeadZone * a_DeltaTime))
		{
			targetPos.y -= m_LookAheadY;
		}
		else if (m_LastPos.y > m_Target->y + (m_DeadZone * a_DeltaTime))
		{
			targetPos.y += m_LookAheadY;
		}

		DXS::Vector3 camPos = Camera::GetMainCamera().GetGameObject()->GetTransform()->GetPosition();
		DXS::Vector2 pos = DXS::Vector2::Lerp(DXS::Vector2(camPos.x, camPos.y), targetPos, m_Speed * a_DeltaTime);
		Camera::GetMainCamera().GetGameObject()->GetTransform()->SetPosition(pos);

		m_LastPos = *m_Target;
	}
}

void CameraController::SetTarget(const DXS::Vector3* a_Target)
{
	m_Target = a_Target;
}

RTTR_REGISTRATION
{
	rttr::registration::class_<CameraController>("CameraController")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("DeadZone", &CameraController::m_DeadZone)
		.property("LookAheadX", &CameraController::m_LookAheadX)
		.property("LookAheadY", &CameraController::m_LookAheadY)
		.property("Speed", &CameraController::m_Speed);
}