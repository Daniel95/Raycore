#pragma once

#include "Core/System/Manager/ISystem.h"
#include "Core/System/Event/Events.h"
#include "Core/Utilities/Log.h"

#include "eventpp/callbacklist.h"
#include "eventpp/callbacklist.h"
#include "eventpp/eventdispatcher.h"

#include <map>
#include <typeinfo> 
#include <crtdbg.h>

namespace Engine
{
    class SystemManager;

    class EventSystem : public ISystem, public SystemRegistry<EventSystem>
    {
        RTTR_ENABLE(ISystem);

    public:
        using EventHandle = typename eventpp::EventDispatcher<Engine::EventType, void(Engine::BaseEvent*)>::Handle;

        EventSystem(SystemManager& a_SystemManager);
        ~EventSystem();

        void Initialize() override;
        void Update(float a_DeltaTime) override;
        void Terminate() override;
        void Dispatch(BaseEvent* a_Event);
        template <typename T>
        EventSystem::EventHandle Subscribe(std::function<void(BaseEvent*)> a_CallBack);
        template <typename T>
        void Unsubscribe(EventSystem::EventHandle a_Handle);

    private:
        eventpp::EventDispatcher<EventType, void(BaseEvent*)> m_EventDispatcher;
        template <typename T>
        EventType GetEventType();

    };

    //The event is deleted after being dispatched.
    inline void EventSystem::Dispatch(BaseEvent* a_Event)
    {
        m_EventDispatcher.dispatch(a_Event->GetEventType(), a_Event);
        delete a_Event;
    }

    template <typename T>
    inline EventSystem::EventHandle EventSystem::Subscribe(std::function<void(BaseEvent*)> a_CallBack)
    {
        static_assert(std::is_base_of<BaseEvent, T>::value, "Type must derive from BaseEvent");

        EventType eventType = GetEventType<T>();
        return m_EventDispatcher.appendListener(eventType, a_CallBack);
    }

    template <typename T>
    inline void EventSystem::Unsubscribe(EventSystem::EventHandle a_Handle)
    {
        static_assert(std::is_base_of<BaseEvent, T>::value, "Type must derive from BaseEvent");

        EventType eventType = GetEventType<T>();
        bool success = m_EventDispatcher.removeListener(eventType, a_Handle);
        _ASSERT(success);
    }

    template<typename T>
    inline EventType EventSystem::GetEventType()
    {
        static_assert(std::is_base_of<BaseEvent, T>::value, "Type must derive from BaseEvent");

        T* type = new T();
        BaseEvent* baseEvent = static_cast<BaseEvent*>(type);
        EventType eventType = baseEvent->GetEventType();

        delete type;

        return eventType;
    }
}