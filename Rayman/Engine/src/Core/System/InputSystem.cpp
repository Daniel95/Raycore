#include "RayCorePCH.h"

#include "Core/System/InputSystem.h"
#include "Core/System/EventSystem.h"
#include "Core/System/Event/Events.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/Application.h"
#include "Core/Utilities/Log.h"

namespace Engine
{
    InputSystem::InputSystem(SystemManager& a_SystemManager)
        : ISystem(a_SystemManager)
    {
    }

    InputSystem::~InputSystem()
    {
    }

    void InputSystem::Initialize()
    {
    }

    void InputSystem::Update(float a_DeltaTime)
    {
        for (KeyCode::Key key : m_KeyboardKeys)
        {
            m_SystemManager.GetSystem<EventSystem>().Dispatch(new KeyboardKeyEvent(key));
        }

        m_KeyboardKeysDown.clear();
        m_KeyboardKeysUp.clear();

        a_DeltaTime;
    }

    void InputSystem::Terminate()
    {
    }

    bool InputSystem::GetKeyboardKeyDown(KeyCode::Key a_Key) const
    {
        bool isDown = std::find(m_KeyboardKeysDown.begin(), m_KeyboardKeysDown.end(), a_Key) != m_KeyboardKeysDown.end();
        return isDown;
    }

    bool InputSystem::GetKeyboardKey(KeyCode::Key a_Key) const
    {
        bool isDown = std::find(m_KeyboardKeys.begin(), m_KeyboardKeys.end(), a_Key) != m_KeyboardKeys.end();
        return isDown;
    }

    bool InputSystem::GetKeyboardKeyUp(KeyCode::Key a_Key) const
    {
        bool isUp = std::find(m_KeyboardKeysUp.begin(), m_KeyboardKeysUp.end(), a_Key) != m_KeyboardKeysUp.end();
        return isUp;
    }     

    void InputSystem::OnKeyPressed(KeyEventArgs& a_KeyEventArgs)
    {
        bool inputExists = std::find(m_KeyboardKeys.begin(), m_KeyboardKeys.end(), a_KeyEventArgs.Key) != m_KeyboardKeys.end();

        if (!inputExists)
        {
            m_KeyboardKeysDown.push_back(a_KeyEventArgs.Key);
            m_KeyboardKeys.push_back(a_KeyEventArgs.Key);
            m_SystemManager.GetSystem<EventSystem>().Dispatch(new KeyboardKeyDownEvent(&a_KeyEventArgs));
        }
    }

    void InputSystem::OnKeyReleased(KeyEventArgs& a_KeyEventArgs)
    {
        bool inputExists = std::find(m_KeyboardKeys.begin(), m_KeyboardKeys.end(), a_KeyEventArgs.Key) != m_KeyboardKeys.end();

        if (inputExists)
        {
            m_KeyboardKeys.erase(std::remove(m_KeyboardKeys.begin(), m_KeyboardKeys.end(), a_KeyEventArgs.Key));
            m_KeyboardKeysUp.push_back(a_KeyEventArgs.Key);
            m_SystemManager.GetSystem<EventSystem>().Dispatch(new KeyboardKeyUpEvent(&a_KeyEventArgs));
        }
    }

    void InputSystem::OnMouseMoved(MouseMotionEventArgs& a_MouseMotionEventArgs)
    {
        m_SystemManager.GetSystem<EventSystem>().Dispatch(new MouseMovedEvent(&a_MouseMotionEventArgs));
    }

    void InputSystem::OnMouseButtonPressed(MouseButtonEventArgs& a_MouseButtonEventArgs)
    {
        m_SystemManager.GetSystem<EventSystem>().Dispatch(new MouseButtonPressedEvent(&a_MouseButtonEventArgs));
    }

    void InputSystem::OnMouseButtonReleased(MouseButtonEventArgs& a_MouseButtonEventArgs)
    {
        m_SystemManager.GetSystem<EventSystem>().Dispatch(new MouseButtonUpEvent(&a_MouseButtonEventArgs));
    }

    void InputSystem::OnMouseWheel(MouseWheelEventArgs& a_MouseWheelEventArgs)
    {
        m_SystemManager.GetSystem<EventSystem>().Dispatch(new MouseWheelEvent(&a_MouseWheelEventArgs));
    }
}