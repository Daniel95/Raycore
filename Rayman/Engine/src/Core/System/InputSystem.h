#pragma once

#include "Core/System/Manager/ISystem.h"
#include "KeyCodes.h"

class KeyEventArgs;
class KeyEventArgs;
class MouseMotionEventArgs;
class MouseButtonEventArgs;
class MouseButtonEventArgs;
class MouseWheelEventArgs;

namespace Engine
{
    class Application;
    class SystemManager;

    class InputSystem : public ISystem, public SystemRegistry<InputSystem>
    {
        RTTR_ENABLE(ISystem);

    public:
        InputSystem(SystemManager& a_SystemManager);
        ~InputSystem();

        void Initialize() override;
        void Update(float a_DeltaTime) override;
        void Terminate() override;

        bool GetKeyboardKeyDown(KeyCode::Key a_Key) const;
        bool GetKeyboardKey(KeyCode::Key a_Key) const;
        bool GetKeyboardKeyUp(KeyCode::Key a_Key) const;

        void OnKeyPressed(KeyEventArgs& a_KeyEventArgs);
        void OnKeyReleased(KeyEventArgs& a_KeyEventArgs);
        void OnMouseMoved(MouseMotionEventArgs& a_MouseMotionEventArgs);
        void OnMouseButtonPressed(MouseButtonEventArgs& a_MouseButtonEventArgs);
        void OnMouseButtonReleased(MouseButtonEventArgs& a_MouseButtonEventArgs);
        void OnMouseWheel(MouseWheelEventArgs& a_MouseWheelEventArgs);

    private:
        std::vector<KeyCode::Key> m_KeyboardKeysDown;
        std::vector<KeyCode::Key> m_KeyboardKeys;
        std::vector<KeyCode::Key> m_KeyboardKeysUp;

    };
};
