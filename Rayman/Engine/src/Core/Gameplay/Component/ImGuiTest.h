#pragma once
#include "Component.h"

#include "Core/Utilities/Math/SimpleMath.h"

#include <rttr/registration_friend>
#include <stdint.h>

#include <string>
#include <vector>

namespace Engine
{
    class GameObject;

    enum class E_Enumeration
    {
        First   ,
        Second  ,
        Third   ,
        Fourth  
    };

    struct S_Struct
    {
        int ID = 2;
    };

    class ImGuiTest : public Component
    {
        RTTR_ENABLE(Component, Inspectable);
        RTTR_REGISTRATION_FRIEND;

    public:
        ImGuiTest();
        virtual ~ImGuiTest();

        void Inspect() override;

    private:
        bool m_BoolValue = false;
        char m_CharValue = ' ';
        int8_t m_ByteValue = -8;
        int16_t m_ShortValue = -16;
        int32_t m_IntValue = -32;
        int64_t m_LongValue = -64;
        uint8_t m_UnsignedByteValue = 8;
        uint16_t m_UnsignedShortValue = 16;
        uint32_t m_UnsignedIntValue = 32;
        uint64_t m_UnsignedLongValue = 64;
        float m_FloatValue = 32.32f;
        double m_DoubleValue = 64.64;
        std::string m_StringValue = "Hello World!";
        E_Enumeration m_Enumeration = E_Enumeration::Second;
        std::vector<int> m_IntVector = { 1, 2, 3 };
        DXS::Vector2 m_Vector2 = { 4.5f, 6.7f };

        S_Struct m_Struct;
        std::vector<DXS::Vector2> m_VectorVector = {{ 1.f, 2.f }, { 3.f, 4.f }};

    };
}
