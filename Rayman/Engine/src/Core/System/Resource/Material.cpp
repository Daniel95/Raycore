#include "RayCorePCH.h"

#include "Material.h"
#include "Graphics/DX12Material.h"

Engine::Material::Material(ullong a_ID, const std::string& a_Path) :
	Resource(a_ID, a_Path)
{
	m_DX12Material = DX12Material::White;
}

Engine::Material::~Material()
{
}