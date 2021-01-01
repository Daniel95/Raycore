#pragma once

#include "Core/System/Resource/Resource.h"
#include <DX12Mesh.h>
#include <memory>

namespace Engine
{
	class Mesh : public Resource
	{
	public:
		Mesh(ullong a_ID, const std::string& a_Path);
		~Mesh();

		std::unique_ptr<DX12Mesh> m_DX12Mesh = nullptr;

	protected:
	private:
	};
}