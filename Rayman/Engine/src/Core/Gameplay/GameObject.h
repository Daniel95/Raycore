#pragma once

#include "Core/Gameplay/Component/Component.h"
#include "Core/Utilities/Inspectable.h"
#include "Core/Utilities/Log.h"

#include <rttr/registration>

#include <vector>

namespace Engine 
{
    class Scene;
    class Transform;
    class SystemManager;

	class GameObject : public Inspectable
	{
        RTTR_ENABLE(Inspectable);

	public:
        GameObject();
		~GameObject();

        void Init(Scene& a_Scene);
        void Update(float a_DeltaTime);
        void FixedUpdate(float a_TimeStep);
        void Enable();
        void Disable();

        virtual void Inspect() override;

        template <class T>
        bool HasComponent();
        template <class T>
        T& AddComponent();
        template <class T>
        void RemoveComponent();
        template <class T>
        T* GetComponent() const;

        void AddRawComponent(Component* a_Component) { m_Components.push_back(a_Component); };

        Scene* GetScene() const;
        SystemManager* GetSystemManager() const;
        Transform* GetTransform() const;

        const std::vector<Component*>& GetComponents();
        void SetComponents(const std::vector<Component*>& a_Components);
        void Destroy();

	private:
        std::vector<Component*> m_Components;
        Scene* m_Scene;
        SystemManager* m_SystemManager;
        bool m_Destroyed = false;

	};

    template<class T>
    inline bool GameObject::HasComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "Type must derive from Component");
        
        return GetComponent<T>() != nullptr;
    }

    template<class T>
    inline T& GameObject::AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "Type must derive from Component");
        _ASSERT(!HasComponent<T>());

        T* type = new T();

        Component* component = static_cast<Component*>(type);
        component->Init(this);
        m_Components.push_back(component);

        return *type;
    }

    template<class T>
    inline void GameObject::RemoveComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "Type must derive from Component");

        T* componentOfType = GetComponent<T>();

        _ASSERT(componentOfType != nullptr);

        Component* component = static_cast<Component*>(componentOfType);

        m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
    }

    template<class T>
    inline T* GameObject::GetComponent() const
    {
        static_assert(std::is_base_of<Component, T>::value, "Type must derive from Component");

        T* componentOfType = nullptr;

        for (Component* component : m_Components)
        {
            componentOfType = dynamic_cast<T*>(component);

            if (componentOfType != nullptr)
            {
                break;
            }
        }

        return componentOfType;
    }
}