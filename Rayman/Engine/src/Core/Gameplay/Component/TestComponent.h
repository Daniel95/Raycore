#pragma once

#include "Core/Gameplay/Component/Component.h"
#include <rttr/registration_friend>

namespace Engine
{
    class TestComponent : public Component
    {
        RTTR_ENABLE(Component, Inspectable);
        RTTR_REGISTRATION_FRIEND;

    public:
        TestComponent();
        virtual ~TestComponent();

        void Inspect() override;

    };
}