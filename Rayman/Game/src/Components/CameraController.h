#pragma once
#include "Core/Gameplay/Component/Component.h"
#include "Core/Utilities/Math/SimpleMath.h"

using namespace Engine;

class CameraController : public Component
{
public:
	CameraController();
	virtual ~CameraController();

	virtual void Init(GameObject* a_GameObject) override;
	virtual void Update(float a_DeltaTime) override;

	void SetTarget(const DXS::Vector3* a_Target);
	
	float m_DeadZone = 1.0f;
	float m_LookAheadX = 5.0f;
	float m_LookAheadY = 1.0f;
	float m_Speed = 2.5f;

	RTTR_ENABLE(Component);

private:
	const DXS::Vector3* m_Target = nullptr;
	DXS::Vector3 m_LastPos = DXS::Vector3::Zero;
	bool m_HasSetPlayer = false;
};