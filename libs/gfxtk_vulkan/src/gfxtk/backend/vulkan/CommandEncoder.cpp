#include "CommandEncoder.hpp"
#include <vector>
#include <gfxtk/log.hpp>
#include "TextureAspect.hpp"
#include "AccessFlags.hpp"

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

void gfxtk::backend::CommandEncoder::copyBufferToBuffer(
        std::unique_ptr<backend::Buffer> const& source,
        size_t sourceOffset,
        std::unique_ptr<backend::Buffer> const& destination,
        size_t destinationOffset,
        size_t copySize
) {
    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = sourceOffset;
    copyRegion.dstOffset = destinationOffset;
    copyRegion.size = copySize;
    vkCmdCopyBuffer(vulkanCommandBuffer, source->vulkanBuffer, destination->vulkanBuffer, 1, &copyRegion);
}

void gfxtk::backend::CommandEncoder::copyBufferToTexture(
        std::unique_ptr<backend::Buffer> const& buffer,
        size_t offset,
        uint32_t bytesPerRow,
        uint32_t rowsPerImage,
        std::shared_ptr<backend::Texture> const& texture,
        gfxtk::PipelineStage destinationStage,
        gfxtk::TextureLayout destinationTextureLayout,
        gfxtk::Origin3D origin,
        gfxtk::TextureAspect aspect,
        Extent3D copySize
) {
    VkImageMemoryBarrier barrierToWrite{};
    barrierToWrite.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrierToWrite.image = texture->vulkanImage;
    barrierToWrite.srcAccessMask = 0;
    barrierToWrite.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrierToWrite.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    barrierToWrite.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrierToWrite.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrierToWrite.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrierToWrite.subresourceRange.aspectMask = backend::TextureAspect::convert(aspect);
    barrierToWrite.subresourceRange.baseMipLevel = 0;
    barrierToWrite.subresourceRange.levelCount = 1;
    barrierToWrite.subresourceRange.baseArrayLayer = 0;
    barrierToWrite.subresourceRange.layerCount = 1;

    vkCmdPipelineBarrier(
            vulkanCommandBuffer,
            VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            0,
            0, nullptr,
            0, nullptr,
            1, &barrierToWrite
    );

    VkBufferImageCopy bufferImageCopy{};
    bufferImageCopy.bufferOffset = offset;
    bufferImageCopy.bufferRowLength = bytesPerRow;
    bufferImageCopy.bufferImageHeight = rowsPerImage;
    bufferImageCopy.imageSubresource.baseArrayLayer = 0;
    bufferImageCopy.imageSubresource.layerCount = 1;
    bufferImageCopy.imageSubresource.mipLevel = 0;
    bufferImageCopy.imageSubresource.aspectMask = backend::TextureAspect::convert(aspect);
    bufferImageCopy.imageExtent = {copySize.width, copySize.height, copySize.depth};
    bufferImageCopy.imageOffset = {int32_t(origin.x), int32_t(origin.y), int32_t(origin.z)};

    vkCmdCopyBufferToImage(
            vulkanCommandBuffer,
            buffer->vulkanBuffer,
            texture->vulkanImage,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1,
            &bufferImageCopy
    );

    VkAccessFlags destinationAccessFlags = 0;

    switch (destinationTextureLayout) {
        case gfxtk::TextureLayout::General:
            // This just seems wrong...
            destinationAccessFlags =
                    VK_ACCESS_INDEX_READ_BIT |
                    VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT |
                    VK_ACCESS_UNIFORM_READ_BIT |
                    VK_ACCESS_INPUT_ATTACHMENT_READ_BIT |
                    VK_ACCESS_SHADER_READ_BIT |
                    VK_ACCESS_SHADER_WRITE_BIT |
                    VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                    VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                    VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
                    VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT |
                    VK_ACCESS_TRANSFER_READ_BIT |
                    VK_ACCESS_TRANSFER_WRITE_BIT |
                    VK_ACCESS_HOST_READ_BIT |
                    VK_ACCESS_HOST_WRITE_BIT;
            break;
        case gfxtk::TextureLayout::ColorAttachment:
            destinationAccessFlags =
                    VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                    VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            break;
        case gfxtk::TextureLayout::ColorAttachmentReadOnly:
            destinationAccessFlags = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
            break;
        case gfxtk::TextureLayout::DepthStencilAttachment:
            destinationAccessFlags =
                    VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
                    VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
            break;
        case gfxtk::TextureLayout::DepthStencilReadOnly:
            destinationAccessFlags = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
            break;
        case gfxtk::TextureLayout::ShaderReadOnly:
            destinationAccessFlags = VK_ACCESS_SHADER_READ_BIT;
            break;
        case gfxtk::TextureLayout::TransferSource:
            destinationAccessFlags = VK_ACCESS_TRANSFER_READ_BIT;
            break;
        case gfxtk::TextureLayout::TransferDestination:
            destinationAccessFlags = VK_ACCESS_TRANSFER_WRITE_BIT;
            break;
        case gfxtk::TextureLayout::PresentSource:
            destinationAccessFlags = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
            break;
        default:
            GFXTK_LOG_F("unsupported `TextureLayout` found in `copyBufferToTexture` on Vulkan backend!");
            break;
    }

    VkImageMemoryBarrier barrierToRead{};
    barrierToRead.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrierToRead.image = texture->vulkanImage;
    barrierToRead.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrierToRead.dstAccessMask = destinationAccessFlags;
    barrierToRead.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrierToRead.newLayout = backend::TextureLayout::convert(destinationTextureLayout);
    barrierToRead.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrierToRead.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrierToRead.subresourceRange.aspectMask = backend::TextureAspect::convert(aspect);
    barrierToRead.subresourceRange.baseMipLevel = 0;
    barrierToRead.subresourceRange.levelCount = 1;
    barrierToRead.subresourceRange.baseArrayLayer = 0;
    barrierToRead.subresourceRange.layerCount = 1;

    vkCmdPipelineBarrier(
            vulkanCommandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            backend::PipelineStage::convert(destinationStage),
            0,
            0, nullptr,
            0, nullptr,
            1, &barrierToRead
    );
}
