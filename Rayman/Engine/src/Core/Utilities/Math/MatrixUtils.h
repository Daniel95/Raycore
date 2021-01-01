#pragma once

#include <DX12LibPCH.h>
using namespace DirectX;

#include <DirectXMath.h>

namespace Engine
{
	struct DX12Matrix;

	namespace MatrixUtils
	{
		// Builds a look-at (world) matrix from a point, up and direction vectors.
		XMMATRIX XM_CALLCONV LookAtMatrix(FXMVECTOR a_Position, FXMVECTOR a_Direction, FXMVECTOR a_Up);
		void XM_CALLCONV ComputeMatrices(FXMMATRIX model, CXMMATRIX view, CXMMATRIX viewProjection, DX12Matrix& mat);
	}
}