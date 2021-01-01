#pragma once

#include "Core/System/InputSystem.h"

namespace Engine
{
    enum class EventType
    {
        //Inputs
        KeyPressed,
        KeyHolding,
        KeyReleased,
        MouseMoved,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseWheel,

        //Scene
        //SceneLoaded,
    };

    class BaseEvent
    {
    public:
        BaseEvent() = default;
        virtual EventType GetEventType() = 0;
    };

    class KeyboardKeyDownEvent : public BaseEvent
    {
    public:
        KeyboardKeyDownEvent() = default;
        KeyboardKeyDownEvent(KeyEventArgs* a_KeyEventArgs)
        {
            m_KeyEventArgs = a_KeyEventArgs;
        }

        inline virtual EventType GetEventType()
        {
            return EventType::KeyPressed;
        };

        KeyEventArgs* m_KeyEventArgs;
    };

    class KeyboardKeyUpEvent : public BaseEvent
    {
    public:
        KeyboardKeyUpEvent() = default;
        KeyboardKeyUpEvent(KeyEventArgs* a_KeyEventArgs)
        {
            m_KeyEventArgs = a_KeyEventArgs;
        }

        inline virtual EventType GetEventType()
        {
            return EventType::KeyReleased;
        };

        KeyEventArgs* m_KeyEventArgs;
    };

    class KeyboardKeyEvent : public BaseEvent
    {
    public:
        KeyboardKeyEvent() = default;
        KeyboardKeyEvent(KeyCode::Key a_Key)
        {
            m_Key = a_Key;
        }

        inline virtual EventType GetEventType()
        {
            return EventType::KeyHolding;
        };

        KeyCode::Key m_Key;
    };

    class MouseMovedEvent : public BaseEvent
    {
    public:
        MouseMovedEvent() = default;
        MouseMovedEvent(MouseMotionEventArgs* a_MouseMotionEventArgs)
        {
            m_MouseMotionEventArgs = a_MouseMotionEventArgs;
        }

        inline virtual EventType GetEventType()
        {
            return EventType::MouseMoved;
        };

        MouseMotionEventArgs* m_MouseMotionEventArgs;
    };

    class MouseButtonPressedEvent : public BaseEvent
    {
    public:
        MouseButtonPressedEvent() = default;
        MouseButtonPressedEvent(MouseButtonEventArgs* a_MouseButtonEventArgs)
        {
            m_MouseButtonEventArgs = a_MouseButtonEventArgs;
        }

        inline virtual EventType GetEventType()
        {
            return EventType::MouseButtonPressed;
        };

        MouseButtonEventArgs* m_MouseButtonEventArgs;
    };

    class MouseButtonUpEvent : public BaseEvent
    {
    public:
        MouseButtonUpEvent() = default;
        MouseButtonUpEvent(MouseButtonEventArgs* a_MouseButtonEventArgs)
        {
            m_MouseButtonEventArgs = a_MouseButtonEventArgs;
        }

        inline virtual EventType GetEventType()
        {
            return EventType::MouseButtonReleased;
        };

        MouseButtonEventArgs* m_MouseButtonEventArgs;
    };

    class MouseWheelEvent : public BaseEvent
    {
    public:
        MouseWheelEvent() = default;
        MouseWheelEvent(MouseWheelEventArgs* a_MouseWheelEventArgs)
        {
            m_MouseWheelEventArgs = a_MouseWheelEventArgs;
        }

        inline virtual EventType GetEventType()
        {
            return EventType::MouseWheel;
        };

        MouseWheelEventArgs* m_MouseWheelEventArgs;
    };
}