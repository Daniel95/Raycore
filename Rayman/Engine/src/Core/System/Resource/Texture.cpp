#include "RayCorePCH.h"

#include "Core/System/Resource/Texture.h"
#include "../ResourceSystem.h"

namespace Engine
{
    Texture::Texture(ullong a_ID, const std::string& a_Path)
        : Resource(a_ID, a_Path)
    {
		ResourceSystem::AddTextureToLoad(this);

		//auto commandQueue = DX12Graphics::Get().GetCommandQueue(D3D12_COMMAND_LIST_TYPE_COPY);
		//auto commandList = commandQueue->GetCommandList();

		//std::wstring wPath;
		//wPath.assign(a_Path.begin(), a_Path.end());

		//commandList->LoadTextureFromFile(m_DX12Texture, wPath);

		//auto fenceValue = commandQueue->ExecuteCommandList(commandList);
		//commandQueue->WaitForFenceValue(fenceValue);
    }

    Texture::~Texture()
    {
    }
}