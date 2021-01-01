#include "MatrixUtils.h"
#include "Core/Utilities/Math/DX12Matrix.h"

XMMATRIX XM_CALLCONV Engine::MatrixUtils::LookAtMatrix(FXMVECTOR a_Position, FXMVECTOR a_Direction, FXMVECTOR a_Up)
{
	assert(!XMVector3Equal(a_Direction, XMVectorZero()));
	assert(!XMVector3IsInfinite(a_Direction));
	assert(!XMVector3Equal(a_Up, XMVectorZero()));
	assert(!XMVector3IsInfinite(a_Up));

	XMVECTOR R2 = XMVector3Normalize(a_Direction);

	XMVECTOR R0 = XMVector3Cross(a_Up, R2);
	R0 = XMVector3Normalize(R0);

	XMVECTOR R1 = XMVector3Cross(R2, R0);

	XMMATRIX M(R0, R1, R2, a_Position);

	return M;
}

void XM_CALLCONV Engine::MatrixUtils::ComputeMatrices(FXMMATRIX a_ModelMat, CXMMATRIX a_ViewMat, CXMMATRIX a_ViewProjectionMat, DX12Matrix& a_DX12Mat)
{
	a_DX12Mat.m_ModelMatrix = a_ModelMat;
	a_DX12Mat.m_ModelViewMatrix = a_ModelMat * a_ViewMat;
	a_DX12Mat.m_InverseTransposeModelViewMatrix = XMMatrixTranspose(XMMatrixInverse(nullptr, a_DX12Mat.m_ModelViewMatrix));
	a_DX12Mat.m_ModelViewProjectionMatrix = a_ModelMat * a_ViewProjectionMat;
}