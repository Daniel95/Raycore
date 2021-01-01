#pragma once

#include "Core/Utilities/Inspectable.h"

#include <rttr/registration>
#include <rttr/registration_friend>

namespace Engine
{
    class GameObject;
    class BoxCollider2D;

    class Component : public Inspectable
    {
        RTTR_ENABLE(Inspectable);

    public:
        Component();
        virtual ~Component();

        virtual void Init(GameObject* a_GameObject);
        virtual void Update(float a_DeltaTime);
        virtual void FixedUpdate(float a_TimeStep);
        virtual void Inspect() override;

        virtual void OnCollide(bool a_IsLeft, BoxCollider2D* a_ThisComponent, BoxCollider2D* a_OtherComponent);
		void Enable();
        void Disable();

        GameObject* GetGameObject();
		const bool& IsEnabled() { return m_isEnabled; };

		RTTR_REGISTRATION_FRIEND;

	protected:
		virtual void OnEnable();
		virtual void OnDisable();

    private:
        GameObject* m_GameObject;
		bool m_isEnabled = true;
    };
}
