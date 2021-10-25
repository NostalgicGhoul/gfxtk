#include <gfxtk/log.hpp>
#include "RenderPassAttachment.hpp"
#include "PixelFormat.hpp"
#include "LoadOp.hpp"
#include "StoreOp.hpp"
#include "TextureLayout.hpp"

std::shared_ptr<gfxtk::backend::RenderPassAttachment> gfxtk::backend::RenderPassAttachment::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        gfxtk::RenderPassAttachmentDescriptor const& descriptor
) {
    std::vector<VkAttachmentDescription> vulkanAttachments;
    vulkanAttachments.reserve(descriptor.colorAttachments.size());
    std::vector<VkAttachmentReference> vulkanColorAttachmentReferences;
    vulkanColorAttachmentReferences.reserve(descriptor.colorAttachments.size());
    VkAttachmentReference vulkanDepthStencilAttachmentReference{};

    for (auto const& colorAttachment : descriptor.colorAttachments) {
        VkAttachmentDescription vulkanColorAttachment{};
        vulkanColorAttachment.format = backend::PixelFormat::convertToVkFormat(colorAttachment.pixelFormat);
        vulkanColorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        vulkanColorAttachment.loadOp = backend::LoadOp::convert(colorAttachment.loadOp);
        vulkanColorAttachment.storeOp = backend::StoreOp::convert(colorAttachment.storeOp);
        vulkanColorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        vulkanColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        vulkanColorAttachment.initialLayout = backend::TextureLayout::convert(colorAttachment.initialLayout);
        vulkanColorAttachment.finalLayout = backend::TextureLayout::convert(colorAttachment.finalLayout);
        vulkanAttachments.push_back(vulkanColorAttachment);

        VkAttachmentReference vulkanAttachmentReference{};
        vulkanAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        vulkanAttachmentReference.attachment = static_cast<uint32_t>(vulkanColorAttachmentReferences.size());
        vulkanColorAttachmentReferences.push_back(vulkanAttachmentReference);
    }

    if (descriptor.depthStencilAttachment.has_value()) {
        VkAttachmentDescription vulkanDepthAttachment{};
        vulkanDepthAttachment.format =
                backend::PixelFormat::convertToVkFormat(descriptor.depthStencilAttachment->pixelFormat);
        vulkanDepthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        vulkanDepthAttachment.loadOp = backend::LoadOp::convert(descriptor.depthStencilAttachment->depthLoadOp);
        vulkanDepthAttachment.storeOp = backend::StoreOp::convert(descriptor.depthStencilAttachment->depthStoreOp);
        vulkanDepthAttachment.stencilLoadOp =
                backend::LoadOp::convert(descriptor.depthStencilAttachment->stencilLoadOp);
        vulkanDepthAttachment.stencilStoreOp =
                backend::StoreOp::convert(descriptor.depthStencilAttachment->stencilStoreOp);
        vulkanDepthAttachment.initialLayout =
                backend::TextureLayout::convert(descriptor.depthStencilAttachment->initialLayout);
        vulkanDepthAttachment.finalLayout =
                backend::TextureLayout::convert(descriptor.depthStencilAttachment->finalLayout);
        vulkanAttachments.push_back(vulkanDepthAttachment);

        vulkanDepthStencilAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        vulkanDepthStencilAttachmentReference.attachment =
                static_cast<uint32_t>(vulkanColorAttachmentReferences.size());
    }

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = static_cast<uint32_t>(vulkanColorAttachmentReferences.size());
    subpass.pColorAttachments = vulkanColorAttachmentReferences.data();

    if (descriptor.depthStencilAttachment.has_value()) {
        subpass.pDepthStencilAttachment = &vulkanDepthStencilAttachmentReference;
    }

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(vulkanAttachments.size());
    renderPassInfo.pAttachments = vulkanAttachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    VkRenderPass renderPass;

    if (vkCreateRenderPass(backendDevice->logicalDevice, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create RenderPassAttachment for `Vulkan` backend!");
    }

    return std::make_shared<RenderPassAttachment>(backendDevice->logicalDevice, renderPass);
}
