#include "RayCorePCH.h"

#include "Resource.h"

namespace Engine
{
    Engine::Resource::Resource(ullong a_ID, const std::string& a_Path)
    {
        m_ID = a_ID;
        m_Path = a_Path;
    }

    void Resource::Reload()
    {
    }

    RTTR_REGISTRATION
    {
        rttr::registration::class_<Resource>("Resource")
            .constructor<ullong, const std::string&>()
            (
                rttr::policy::ctor::as_raw_ptr
            );
    }
}