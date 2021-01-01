#include "RayCorePCH.h"

#include "Core/Gameplay/Component/ImGuiTest.h"

#include "Core/Gameplay/GameObject.h"
#include "Core/Utilities/Log.h"

namespace Engine
{
    ImGuiTest::ImGuiTest()
    {

    }

    ImGuiTest::~ImGuiTest()
    {

    }

    void ImGuiTest::Inspect()
    {

    }
}

RTTR_REGISTRATION
{
    rttr::registration::enumeration<Engine::E_Enumeration>("E_Enumeration")
        (
            rttr::value("First",    Engine::E_Enumeration::First),
            rttr::value("Second",   Engine::E_Enumeration::Second),
            rttr::value("Third",    Engine::E_Enumeration::Third),
            rttr::value("Fourth",   Engine::E_Enumeration::Fourth)
        )
    ;

    rttr::registration::class_<Engine::ImGuiTest>("ImGuiTest")
        .constructor<>()
        (
            rttr::policy::ctor::as_raw_ptr
        )
        .property("Boolean",            &Engine::ImGuiTest::m_BoolValue,            rttr::registration::private_access)
        .property("Character",          &Engine::ImGuiTest::m_CharValue,            rttr::registration::private_access)
        .property("Byte",               &Engine::ImGuiTest::m_ByteValue,            rttr::registration::private_access)
        .property("Short",              &Engine::ImGuiTest::m_ShortValue,           rttr::registration::private_access)
        .property("Integer",            &Engine::ImGuiTest::m_IntValue,             rttr::registration::private_access)
        .property("Long",               &Engine::ImGuiTest::m_LongValue,            rttr::registration::private_access)
        .property("UnsignedByte",       &Engine::ImGuiTest::m_UnsignedByteValue,    rttr::registration::private_access)
        .property("UnsignedShort",      &Engine::ImGuiTest::m_UnsignedShortValue,   rttr::registration::private_access)
        .property("UnsignedInteger",    &Engine::ImGuiTest::m_UnsignedIntValue,     rttr::registration::private_access)
        .property("UnsignedLong",       &Engine::ImGuiTest::m_UnsignedLongValue,    rttr::registration::private_access)
        .property("Float",              &Engine::ImGuiTest::m_FloatValue,           rttr::registration::private_access)
        .property("Double",             &Engine::ImGuiTest::m_DoubleValue,          rttr::registration::private_access)
        .property("String",             &Engine::ImGuiTest::m_StringValue,          rttr::registration::private_access)
        .property("Enumeration",        &Engine::ImGuiTest::m_Enumeration,          rttr::registration::private_access)
        .property("IntVector",          &Engine::ImGuiTest::m_IntVector,            rttr::registration::private_access)
        .property("Vector2",            &Engine::ImGuiTest::m_Vector2,              rttr::registration::private_access)
        .property("Struct",             &Engine::ImGuiTest::m_Struct,               rttr::registration::private_access)
        .property("VectorofVectors",    &Engine::ImGuiTest::m_VectorVector,         rttr::registration::private_access)
    ;
}
