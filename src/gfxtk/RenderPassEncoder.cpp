#include "RenderPassEncoder.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/RenderPassEncoder.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/RenderPassEncoder.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::RenderPassEncoder::RenderPassEncoder(std::unique_ptr<backend::RenderPassEncoder> backendRenderPassEncoder)
        : _backendRenderPassEncoder(std::move(backendRenderPassEncoder)) {}

gfxtk::RenderPassEncoder::~RenderPassEncoder() = default;

void gfxtk::RenderPassEncoder::setPipeline(gfxtk::Pipeline const& pipeline) {
    _backendRenderPassEncoder->setPipeline(pipeline._backendPipeline);
}

void gfxtk::RenderPassEncoder::setIndexBuffer(gfxtk::Buffer const& buffer, gfxtk::IndexType type, size_t offset) {
    _backendRenderPassEncoder->setIndexBuffer(buffer._backendBuffer, type, offset);
}

void gfxtk::RenderPassEncoder::setVertexBuffer(uint32_t binding, gfxtk::Buffer const& buffer, size_t offset) {
    _backendRenderPassEncoder->setVertexBuffer(binding, buffer._backendBuffer, offset);
}

void gfxtk::RenderPassEncoder::draw(
        uint32_t vertexCount,
        uint32_t firstVertex,
        uint32_t instanceCount,
        uint32_t firstInstance
) {
    _backendRenderPassEncoder->draw(vertexCount, firstVertex, instanceCount, firstInstance);
}

void gfxtk::RenderPassEncoder::drawIndexed(
        uint32_t indexCount,
        uint32_t firstIndex,
        int32_t vertexOffset,
        uint32_t instanceCount,
        uint32_t firstInstance
) {
    _backendRenderPassEncoder->drawIndexed(indexCount, firstIndex, vertexOffset, instanceCount, firstInstance);
}

void gfxtk::RenderPassEncoder::drawIndirect(gfxtk::Buffer const& buffer, size_t offset) {
    _backendRenderPassEncoder->drawIndirect(buffer._backendBuffer, offset);
}

void gfxtk::RenderPassEncoder::drawIndexedIndirect(gfxtk::Buffer const& buffer, size_t offset) {
    _backendRenderPassEncoder->drawIndexedIndirect(buffer._backendBuffer, offset);
}

void gfxtk::RenderPassEncoder::endRenderPass() {
    _backendRenderPassEncoder->endRenderPass();
}
