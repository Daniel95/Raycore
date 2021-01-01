#include <DX12LibPCH.h>

#include <Buffer.h>

Buffer::Buffer(const std::wstring& name)
    : DX12Resource(name)
{}

Buffer::Buffer( const D3D12_RESOURCE_DESC& resDesc,
    size_t numElements, size_t elementSize,
    const std::wstring& name )
    : DX12Resource(resDesc, nullptr, name)
{
    CreateViews(numElements, elementSize);
}

void Buffer::CreateViews(size_t numElements, size_t elementSize)
{
    throw std::exception("Unimplemented function.");
}
