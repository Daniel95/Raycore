#pragma once

#include <directxmath.h>

namespace Engine
{
	struct DX12Matrix
	{
		DirectX::XMMATRIX m_ModelMatrix;
		DirectX::XMMATRIX m_ModelViewMatrix;
		DirectX::XMMATRIX m_InverseTransposeModelViewMatrix;
		DirectX::XMMATRIX m_ModelViewProjectionMatrix;
	};
}