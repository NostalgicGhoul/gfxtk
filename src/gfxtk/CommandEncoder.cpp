#include "CommandEncoder.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/CommandEncoder.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/CommandEncoder.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::CommandEncoder gfxtk::CommandEncoder::create(
        std::unique_ptr<backend::CommandBuffer> const& backendCommandBuffer
) {
    return gfxtk::CommandEncoder(backend::CommandEncoder::create(backendCommandBuffer));
}

gfxtk::CommandEncoder::CommandEncoder(std::unique_ptr<backend::CommandEncoder> backendCommandEncoder)
        : _backendCommandEncoder(std::move(backendCommandEncoder)) {}

gfxtk::CommandEncoder::~CommandEncoder() = default;

gfxtk::RenderPassEncoder gfxtk::CommandEncoder::beginRenderPass(
        gfxtk::RenderPassAttachment const& renderPassAttachment,
        gfxtk::Framebuffer const& framebuffer,
        gfxtk::Rect2D renderArea,
        std::vector<ClearColorValue> const& clearColorValues,
        std::optional<ClearDepthStencilValue> clearDepthStencilValue
) {
    return RenderPassEncoder(
            _backendCommandEncoder->beginRenderPass(
                    renderPassAttachment._backendRenderPassAttachment,
                    framebuffer._backendFramebuffer,
                    renderArea,
                    clearColorValues,
                    clearDepthStencilValue
            )
    );
}

void gfxtk::CommandEncoder::endCommandEncoding() {
    _backendCommandEncoder->endCommandEncoding();
}

void gfxtk::CommandEncoder::copyBufferToBuffer(
        gfxtk::Buffer& source,
        size_t sourceOffset,
        gfxtk::Buffer& destination,
        size_t destinationOffset,
        size_t copySize
) {
    _backendCommandEncoder->copyBufferToBuffer(
            source._backendBuffer,
            sourceOffset,
            destination._backendBuffer,
            destinationOffset,
            copySize
    );
}

void gfxtk::CommandEncoder::copyBufferToTexture(
        gfxtk::ImageCopyBuffer const& source,
        gfxtk::ImageCopyTexture const& destination,
        gfxtk::Extent3D copySize
) {
    _backendCommandEncoder->copyBufferToTexture(
            source.buffer._backendBuffer,
            source.offset,
            source.bytesPerRow,
            source.rowsPerImage,
            destination.texture._backendTexture,
            destination.destinationStage,
            destination.destinationTextureLayout,
            destination.origin,
            destination.aspect,
            copySize
    );
}
