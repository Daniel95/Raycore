#pragma once
#include "Core/Gameplay/Component/Component.h"
#include "Core/Utilities/Math/SimpleMath.h"

#include <vector>
#include <rttr/registration_friend>

using namespace Engine;

class Engine::GameObject;

struct ParallaxObject
{
	GameObject* m_GameObject = nullptr;
	float m_OffsetX = 0.f;
	float m_OffsetY = 0.f;
	float m_ParallaxIndex = 1.f;
	float m_MultiplierX = 1.f;
	float m_MultiplierY = 0.5f;
};

class ParalaxScrolling : public Engine::Component
{
public:
	ParalaxScrolling();
	virtual ~ParalaxScrolling();

	virtual void Init(GameObject* a_GameObject) override;
	virtual void Update(float a_DeltaTime) override;

	RTTR_ENABLE(Component);
	RTTR_REGISTRATION_FRIEND;

protected:

private:
	std::vector<ParallaxObject*> m_ObjectsToParalax = std::vector<ParallaxObject*>();

	int m_AmountOfCopies = 5;
};