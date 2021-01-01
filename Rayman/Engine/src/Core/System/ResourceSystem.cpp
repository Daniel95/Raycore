#include "RayCorePCH.h"

#include "Core/System/Manager/SystemManager.h"
#include "Core/System/ResourceSystem.h"
#include "Core/Utilities/Log.h"

#include <imgui.h>
#include <string>
#include <iostream>
//#include <filesystem>

namespace Engine
{
	std::vector<Texture*> ResourceSystem::ms_TexturesToLoad = std::vector<Texture*>();

    ResourceSystem::ResourceSystem(SystemManager& a_SystemManager)
        : ISystem(a_SystemManager)
    {
        m_SubInspectables.push_back(SubInspectable("Loaded Resources", &m_InspectLoadedScenes));
    }

    void ResourceSystem::Initialize()
    {
        char* pValue;
        size_t len;
        _dupenv_s(&pValue, &len, "APPDATA");

        std::string RaymanPCSavePath = std::string(pValue) + std::string("\\RayMan");

        if (!std::experimental::filesystem::exists(RaymanPCSavePath))
        {
            std::experimental::filesystem::create_directory(RaymanPCSavePath);
        }
    }

    std::vector<const Resource*> ResourceSystem::GetAllResources() const
    {
        std::vector<const Resource*> resources;

        for (std::pair<ullong, Resource*> resource : m_Resources)
        {
            resources.push_back(resource.second);
        }

        return resources;
    }

    void ResourceSystem::Update(float a_DeltaTime)
    {
        a_DeltaTime;
    }

	void ResourceSystem::LateUpdate()
	{
		//Quick and dirty fix to load all the textures at the end of the frame when needed before the render loop.
		if (!ms_TexturesToLoad.empty())
		{
			auto commandQueue = DX12Graphics::Get().GetCommandQueue(D3D12_COMMAND_LIST_TYPE_COPY);
			auto commandList = commandQueue->GetCommandList();

			for (Texture* t : ms_TexturesToLoad)
			{
				if (t != nullptr)
				{
					std::wstring wPath;
					wPath.assign(t->Path().begin(), t->Path().end());

					commandList->LoadTextureFromFile(t->m_DX12Texture, wPath);
				}
			}

			auto fenceValue = commandQueue->ExecuteCommandList(commandList);
			commandQueue->WaitForFenceValue(fenceValue);

			ms_TexturesToLoad.clear();
		}
	}

	void ResourceSystem::Terminate()
    {
    }

    void ResourceSystem::Inspect()
    {
        if (m_InspectLoadedScenes)
        {
            if (ImGui::Begin("Resources", &m_InspectLoadedScenes))
            {
                if (ImGui::CollapsingHeader("Available Resources"))
                {
                    InspectResourceFiles(ASSETS_PATH);
                }

                if (ImGui::CollapsingHeader("Loaded Resources"))
                {
                    if (ImGui::SmallButton("Reload Resources"))
                    {
                        LOG_ENGINE_INFO("Reload resources.");
                        for (std::pair<ullong, Resource*> pair : m_Resources)
                        {
                            pair.second->Reload();
                        }
                    }

                    for (std::pair<ullong, Resource*> pair : m_Resources)
                    {
                        Resource* resource = pair.second;
                        ImGui::Text(resource->Path().c_str());
                    }
                }
            }
            ImGui::End();
        }
    }

    void ResourceSystem::InspectResourceFiles(const std::string& a_Path)
    {
        for (const auto& entry : std::experimental::filesystem::directory_iterator(a_Path))
        {
            ImGui::Text(entry.path().u8string().c_str());

            if (std::experimental::filesystem::is_directory(entry))
            {
                InspectResourceFiles(entry.path().u8string());
            } 
        }
    }

	void ResourceSystem::AddTextureToLoad(Texture* a_Texture)
	{
		if (a_Texture != nullptr)
		{
			ms_TexturesToLoad.push_back(a_Texture);
		}
	}

}
