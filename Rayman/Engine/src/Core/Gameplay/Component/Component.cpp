#include "RayCorePCH.h"

#include "Core/Gameplay/Component/Component.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Utilities/Log.h"

namespace Engine 
{
    class BoxCollider2D;
    Component::Component() 
    {
        m_GameObject = nullptr;
    }

    Component::~Component()
    {
    }

    void Component::Init(GameObject* a_GameObject)
    {
        m_GameObject = a_GameObject;

		if (m_isEnabled)
		{
			OnEnable();
		}
		else
		{
			OnDisable();
		}
    }

    void Component::Update(float a_DeltaTime)
    {
        a_DeltaTime;
    }

    void Component::FixedUpdate(float a_TimeStep)
    {
        a_TimeStep;
    }

    void Component::Inspect()
    {

    }

    void Component::OnCollide(bool a_IsLeft, BoxCollider2D* a_ThisComponent, BoxCollider2D* a_OtherComponent)
    {
        a_IsLeft;
        a_ThisComponent;
        a_OtherComponent;
    }

	void Component::Enable()
	{
		m_isEnabled = true;
        OnEnable();
	}

	void Component::Disable()
	{
		m_isEnabled = false;
        OnDisable();
	}

	GameObject* Component::GetGameObject()
    {
        return m_GameObject;
    }

	void Component::OnEnable()
	{
	}

	void Component::OnDisable()
	{
	}

}

RTTR_REGISTRATION
{
	rttr::registration::class_<Engine::Component>("Component")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("Enabled", &Engine::Component::m_isEnabled);
}