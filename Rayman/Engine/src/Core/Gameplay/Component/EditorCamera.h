#pragma once

#include "Core/Gameplay/Component/Camera.h"

namespace Engine
{
    class EditorCamera : public Camera
    {
        RTTR_ENABLE(Camera, Inspectable);
        RTTR_REGISTRATION_FRIEND;

    public:
        EditorCamera();
        ~EditorCamera();

        virtual void Update(float a_DeltaTime) override;

    private:
        const float m_EditorCameraSpeed = 7.0f;

    };
}