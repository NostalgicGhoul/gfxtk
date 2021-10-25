#include "CommandEncoder.hpp"
#include <vector>
#include <gfxtk/log.hpp>

std::unique_ptr<gfxtk::backend::CommandEncoder> gfxtk::backend::CommandEncoder::create(
        std::unique_ptr<backend::CommandBuffer> const& backendCommandBuffer
) {
    return std::make_unique<CommandEncoder>(backendCommandBuffer->vulkanCommandBuffer);
}

gfxtk::backend::CommandEncoder::~CommandEncoder() {
    if (!hasEnded) {
        hasEnded = true;
        endCommandEncoding();
    }
}

std::unique_ptr<gfxtk::backend::RenderPassEncoder> gfxtk::backend::CommandEncoder::beginRenderPass(
        std::shared_ptr<backend::RenderPassAttachment> const& renderPassAttachment,
        std::unique_ptr<backend::Framebuffer> const& framebuffer,
        gfxtk::Rect2D renderArea,
        std::vector<ClearColorValue> const& clearColorValues,
        std::optional<ClearDepthStencilValue> clearDepthStencilValue
) {
    std::vector<VkClearValue> vulkanClearValues;
    vulkanClearValues.reserve(clearColorValues.size());

    for (auto const& clearColorValue : clearColorValues) {
        VkClearValue vulkanClearValue{};
        vulkanClearValue.color = {{clearColorValue.r, clearColorValue.g, clearColorValue.b, clearColorValue.a}};
        vulkanClearValues.push_back(vulkanClearValue);
    }

    if (clearDepthStencilValue.has_value()) {
        VkClearValue vulkanClearDepthStencilValue{};
        vulkanClearDepthStencilValue.depthStencil = {clearDepthStencilValue->depth, clearDepthStencilValue->stencil};
        vulkanClearValues.push_back(vulkanClearDepthStencilValue);
    }

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = renderPassAttachment->vulkanRenderPass;
    renderPassBeginInfo.framebuffer = framebuffer->vulkanFramebuffer;
    renderPassBeginInfo.renderArea.offset = {renderArea.offset.x, renderArea.offset.y};
    renderPassBeginInfo.renderArea.extent = {renderArea.extent.width, renderArea.extent.height};
    renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(vulkanClearValues.size());
    renderPassBeginInfo.pClearValues = vulkanClearValues.data();

    vkCmdBeginRenderPass(vulkanCommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    return gfxtk::backend::RenderPassEncoder::create(vulkanCommandBuffer);
}

void gfxtk::backend::CommandEncoder::endCommandEncoding() {
    hasEnded = true;

    if (vkEndCommandBuffer(vulkanCommandBuffer) != VK_SUCCESS) {
        // TODO: See `vulkan/CommandBuffer.cpp` about future error handling.
        GFXTK_LOG_F("failed to record command buffer on Vulkan backend!");
    }
}
