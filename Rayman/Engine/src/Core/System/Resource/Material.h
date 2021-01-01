#pragma once
#include "Core/System/Resource/Resource.h"
#include "Graphics/DX12Material.h"

namespace Engine
{
	struct DX12Material;

	class Material : public Resource
	{
	public:
		Material(ullong a_ID, const std::string& a_Path);
		~Material();

		DX12Material m_DX12Material = DX12Material::White;

	protected:
	private:
	};
}