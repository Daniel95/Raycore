/**
 * A render target is used to store a set of textures that are the target for 
 * rendering.
 * Maximum number of color textures that can be bound to the render target is 8 
 * (0 - 7) and one depth-stencil buffer.
 */
#pragma once

#include <cstdint>
#include <vector>

#include "DX12Texture.h"

 // Don't use scoped enums to avoid the explicit cast required to use these as 
// array indices.
enum AttachmentPoint
{
    Color0,
    Color1,
    Color2,
    Color3,
    Color4,
    Color5,
    Color6,
    Color7,
    DepthStencil,
    NumAttachmentPoints
};

class RenderTarget
{
public:
    // Create an empty render target.
    RenderTarget();

    RenderTarget( const RenderTarget& copy ) = default;
    RenderTarget( RenderTarget&& copy ) = default;

    RenderTarget& operator=( const RenderTarget& other ) = default;
    RenderTarget& operator=( RenderTarget&& other ) = default;

    // Attach a texture to the render target.
    // The texture will be copied into the texture array.
    void AttachTexture( AttachmentPoint attachmentPoint, const DX12Texture& texture );
    const DX12Texture& GetTexture( AttachmentPoint attachmentPoint ) const;

    // Resize all of the textures associated with the render target.
    void Resize( uint32_t width, uint32_t height );

    // Get a list of the textures attached to the render target.
    // This method is primarily used by the CommandList when binding the
    // render target to the output merger stage of the rendering pipeline.
    const std::vector<DX12Texture>& GetTextures() const;

    // Get the render target formats of the textures currently 
    // attached to this render target object.
    // This is needed to configure the Pipeline state object.
    D3D12_RT_FORMAT_ARRAY GetRenderTargetFormats() const;

    // Get the format of the attached depth/stencil buffer.
    DXGI_FORMAT GetDepthStencilFormat() const;

private:
    
    std::vector<DX12Texture> m_Textures;
};