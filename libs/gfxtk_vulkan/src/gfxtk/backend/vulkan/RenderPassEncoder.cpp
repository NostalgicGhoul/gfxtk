#include "RenderPassEncoder.hpp"
#include "IndexType.hpp"

std::unique_ptr<gfxtk::backend::RenderPassEncoder> gfxtk::backend::RenderPassEncoder::create(
        VkCommandBuffer vulkanCommandBuffer
) {
    return std::make_unique<RenderPassEncoder>(vulkanCommandBuffer);
}

gfxtk::backend::RenderPassEncoder::~RenderPassEncoder() {
    if (!hasEnded) {
        hasEnded = true;
        vkCmdEndRenderPass(vulkanCommandBuffer);
    }
}

void gfxtk::backend::RenderPassEncoder::setPipeline(std::shared_ptr<backend::Pipeline> const& pipeline) {
    vkCmdBindPipeline(vulkanCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->vulkanPipeline);
}

void gfxtk::backend::RenderPassEncoder::setIndexBuffer(
        std::unique_ptr<backend::Buffer> const& buffer,
        gfxtk::IndexType type,
        size_t offset
) {
    vkCmdBindIndexBuffer(vulkanCommandBuffer, buffer->vulkanBuffer, offset, backend::IndexType::convert(type));
}

void gfxtk::backend::RenderPassEncoder::setVertexBuffer(
        uint32_t binding,
        std::unique_ptr<backend::Buffer> const& buffer,
        size_t offset
) {
    VkDeviceSize vkOffset = offset;
    vkCmdBindVertexBuffers(vulkanCommandBuffer, binding, 1, &buffer->vulkanBuffer, &vkOffset);
}

void gfxtk::backend::RenderPassEncoder::setBindGroup(
        std::shared_ptr<backend::PipelineLayout> const& pipelineLayout,
        std::shared_ptr<backend::BindGroup> const& backendBindGroup
) {
    vkCmdBindDescriptorSets(
            vulkanCommandBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            pipelineLayout->vulkanPipelineLayout,
            0,
            1,
            &backendBindGroup->vulkanDescriptorSet,
            0,
            nullptr
    );
}

void gfxtk::backend::RenderPassEncoder::draw(
        uint32_t vertexCount,
        uint32_t firstVertex,
        uint32_t instanceCount,
        uint32_t firstInstance
) {
    vkCmdDraw(vulkanCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

void gfxtk::backend::RenderPassEncoder::drawIndexed(
        uint32_t indexCount,
        uint32_t firstIndex,
        int32_t vertexOffset,
        uint32_t instanceCount,
        uint32_t firstInstance
) {
    vkCmdDrawIndexed(vulkanCommandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

void gfxtk::backend::RenderPassEncoder::drawIndirect(std::unique_ptr<backend::Buffer> const& buffer, size_t offset) {
    // TODO: Is this correct?
    vkCmdDrawIndirect(vulkanCommandBuffer, buffer->vulkanBuffer, offset, 1, 0);
}

void gfxtk::backend::RenderPassEncoder::drawIndexedIndirect(
        std::unique_ptr<backend::Buffer> const& buffer,
        size_t offset
) {
    // TODO: Is this correct?
    vkCmdDrawIndexedIndirect(vulkanCommandBuffer, buffer->vulkanBuffer, offset, 1, 0);
}

void gfxtk::backend::RenderPassEncoder::endRenderPass() {
    hasEnded = true;
    vkCmdEndRenderPass(vulkanCommandBuffer);
}
