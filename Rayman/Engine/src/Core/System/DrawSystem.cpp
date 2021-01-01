#include "RayCorePCH.h"

#include "DrawSystem.h"

#include "Core/Utilities/Log.h"
#include "Core/System/Draw/DrawData.h"
#include "Graphics/RootParameters.h"

#include "Core/System/Resource/Material.h"
#include "Graphics/DX12Material.h"

#include "Core/System/Resource/Texture.h"

#include "Core/System/Resource/Mesh.h"


namespace Engine
{
    DrawSystem::DrawSystem(SystemManager& a_SystemManager)
        : ISystem(a_SystemManager)
    {
    }

    DrawSystem::~DrawSystem()
    {
    }

    void DrawSystem::Initialize()
    {
    }

    void DrawSystem::Update(float a_DeltaTime)
    {
        a_DeltaTime;
    }

	void DrawSystem::Render(std::shared_ptr<CommandList> a_CommandList)
	{
		for (const DrawData* o : m_DrawData)
		{
			if (IsDrawDataValid(o))
			{
				a_CommandList->SetGraphicsDynamicConstantBuffer(RootParameters::MatricesCB, *o->m_Maticies);
				a_CommandList->SetGraphicsDynamicConstantBuffer(RootParameters::MaterialCB, o->m_Material->m_DX12Material);
				a_CommandList->SetShaderResourceView(RootParameters::Textures, 0, o->m_Texture->m_DX12Texture, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

				o->m_Mesh->m_DX12Mesh->Draw(*a_CommandList);
			}
		}
	}

    void DrawSystem::Terminate()
    {
    }

	void DrawSystem::AddDrawData(const DrawData* a_DrawData)
	{
		m_DrawData.push_back(a_DrawData);
	}

	void DrawSystem::RemoveDrawData(const DrawData* a_DrawData)
	{
		m_DrawData.erase(std::remove(m_DrawData.begin(), m_DrawData.end(), a_DrawData), m_DrawData.end());
	}

	bool DrawSystem::IsDrawDataValid(const DrawData* a_DrawData)
	{
		bool isValid = true;

		if (a_DrawData == nullptr)
		{
			isValid = false;
		}
		else
		{
			if (a_DrawData->m_Maticies == nullptr)
			{
				isValid = false;
			}

			if (a_DrawData->m_Material == nullptr)
			{
				isValid = false;
			}

			if (a_DrawData->m_Mesh != nullptr)
			{
				if (a_DrawData->m_Mesh->m_DX12Mesh == nullptr)
				{
					isValid = false;
				}
			}
			else
			{
				isValid = false;
			}

			if (a_DrawData->m_Texture != nullptr)
			{
				if (!a_DrawData->m_Texture->m_DX12Texture.IsValid())
				{
					isValid = false;
				}
			}
			else
			{
				isValid = false;
			}
		}	

		if (!isValid)
		{
			LOG_ENGINE_WARN("DrawSystem: Draw data is not valid!");
			//assert(isValid);
		}

		return isValid;
	}
}