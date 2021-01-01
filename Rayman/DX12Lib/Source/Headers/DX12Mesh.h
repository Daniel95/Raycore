/**
 * A mesh class encapsulates the index and vertex buffers for a geometric primitive.
 */
#pragma once

#include <CommandList.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>

#include <DirectXMath.h>
#include <d3d12.h>

#include <wrl.h>

#include <memory> // For std::unique_ptr
#include <vector>

 // Vertex struct holding position, normal vector, and texture mapping information.
struct VertexPositionNormalTexture
{
    VertexPositionNormalTexture()
    { }

    VertexPositionNormalTexture(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& normal, const DirectX::XMFLOAT2& textureCoordinate)
        : position(position),
        normal(normal),
        textureCoordinate(textureCoordinate)
    { }

    VertexPositionNormalTexture(DirectX::FXMVECTOR position, DirectX::FXMVECTOR normal, DirectX::FXMVECTOR textureCoordinate)
    {
        XMStoreFloat3(&this->position, position);
        XMStoreFloat3(&this->normal, normal);
        XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
    }

    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 textureCoordinate;

    static const int InputElementCount = 3;
    static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};

using VertexCollection = std::vector<VertexPositionNormalTexture>;
using IndexCollection = std::vector<uint16_t>;

class DX12Mesh
{
public:

    void Draw(CommandList& commandList, uint32_t instanceCount = 1, uint32_t firstInstance = 0);

    static std::unique_ptr<DX12Mesh> CreateCube(CommandList& commandList, float size = 1, bool rhcoords = false);
    static std::unique_ptr<DX12Mesh> CreateSphere(CommandList& commandList, float diameter = 1, size_t tessellation = 16, bool rhcoords = false);
    static std::unique_ptr<DX12Mesh> CreateCone(CommandList& commandList, float diameter = 1, float height = 1, size_t tessellation = 32, bool rhcoords = false);
    static std::unique_ptr<DX12Mesh> CreateTorus(CommandList& commandList, float diameter = 1, float thickness = 0.333f, size_t tessellation = 32, bool rhcoords = false);
    static std::unique_ptr<DX12Mesh> CreatePlane(CommandList& commandList, float width = 1, float height = 1, bool rhcoords = false);
	static std::unique_ptr<DX12Mesh> CreatePlaneTextured(CommandList& commandList, float startX = 0.0f, float startY = 0.0f, float widthT = 1.0f, float heightT = 1.0f, bool rhcoords = false);
	static std::unique_ptr<DX12Mesh> CreatePlaneByTextureIndex(CommandList& commandList, int index, int texWidth, int texHeight, int tWidth, int tHeight, int tilesPerRow, int margin = 0);

protected:
	friend struct std::default_delete<DX12Mesh>;

	DX12Mesh();
	DX12Mesh(const DX12Mesh& copy) = delete;
	virtual ~DX12Mesh();

	void Initialize(CommandList& commandList, VertexCollection& vertices, IndexCollection& indices, bool rhcoords);

	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;

	UINT m_IndexCount;
private:

};