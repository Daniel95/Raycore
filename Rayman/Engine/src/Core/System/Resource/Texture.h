#pragma once

#include "Core/System/Resource/Resource.h"

#include <DX12Texture.h>

namespace Engine
{
    class Texture : public Resource
    {
        RTTR_ENABLE(Resource);

    public:
        Texture(ullong a_ID, const std::string& a_Path);
        ~Texture();

		DX12Texture m_DX12Texture;

    private:

    };
}
