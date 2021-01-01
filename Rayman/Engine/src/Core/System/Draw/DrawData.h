#pragma once

#include <DX12Mesh.h>

namespace Engine
{
	struct DX12Matrix;
	class Material;
	class Texture;
	class Mesh;

	struct DrawData
	{
		DrawData()
		{
			m_Maticies = new DX12Matrix();
		}

		~DrawData()
		{
			if (m_Maticies != nullptr)
			{
				delete m_Maticies;
			}
		}

		DX12Matrix* m_Maticies = nullptr;
		Material* m_Material = nullptr;
		Texture* m_Texture = nullptr;
		Mesh* m_Mesh = nullptr;
	};
}