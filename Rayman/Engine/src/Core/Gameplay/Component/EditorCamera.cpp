#include "RayCorePCH.h"
#include "EditorCamera.h"

#include "Core/Application.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/Transform.h"
#include "Core/Gameplay/Component/Transform.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/System/InputSystem.h"

namespace Engine 
{

    EditorCamera::EditorCamera()
        : Camera()
    {
        ms_MainCamera = this;
    }

    EditorCamera::~EditorCamera()
    {
    }

    void EditorCamera::Update(float a_DeltaTime)
    {
        InputSystem* inputSystem = &GetGameObject()->GetSystemManager()->GetSystem<InputSystem>();

        if (inputSystem->GetKeyboardKey(KeyCode::A)
            || inputSystem->GetKeyboardKey(KeyCode::Left))
        {
            Camera::GetMainCamera().GetGameObject()->GetTransform()->Move(DXS::Vector2(m_EditorCameraSpeed * a_DeltaTime, 0));
        }

        if (inputSystem->GetKeyboardKey(KeyCode::D)
            || inputSystem->GetKeyboardKey(KeyCode::Right))
        {
            Camera::GetMainCamera().GetGameObject()->GetTransform()->Move(DXS::Vector2(-m_EditorCameraSpeed * a_DeltaTime, 0));
        }

        if (inputSystem->GetKeyboardKey(KeyCode::S)
            || inputSystem->GetKeyboardKey(KeyCode::Down))
        {
            Camera::GetMainCamera().GetGameObject()->GetTransform()->Move(DXS::Vector2(0, m_EditorCameraSpeed * a_DeltaTime));
        }

        if (inputSystem->GetKeyboardKey(KeyCode::W)
            || inputSystem->GetKeyboardKey(KeyCode::Up))
        {
            Camera::GetMainCamera().GetGameObject()->GetTransform()->Move(DXS::Vector2(0, -m_EditorCameraSpeed * a_DeltaTime));
        }
    }

}

RTTR_REGISTRATION
{
    rttr::registration::class_<Engine::EditorCamera>("EditorCamera")
        .constructor<>()
        (
            rttr::policy::ctor::as_raw_ptr
        )
    ;
}
