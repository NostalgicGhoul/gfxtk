#include <gfxtk/log.hpp>
#include "TextureView.hpp"
#include "PixelFormat.hpp"
#include "TextureAspect.hpp"
#include "TextureViewType.hpp"

std::shared_ptr<gfxtk::backend::TextureView> gfxtk::backend::TextureView::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::shared_ptr<backend::Texture> const& backendTexture,
        gfxtk::TextureViewType type,
        gfxtk::PixelFormat format,
        gfxtk::TextureAspect aspect
) {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = backendTexture->vulkanImage;
    createInfo.viewType = backend::TextureViewType::convert(type);
    createInfo.format = backend::PixelFormat::convert(format);
    createInfo.subresourceRange.aspectMask = backend::TextureAspect::convert(aspect);
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;

    if (vkCreateImageView(backendDevice->logicalDevice, &createInfo, nullptr, &imageView) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create `TextureView` on Vulkan backend!");
    }

    return std::make_shared<TextureView>(backendDevice->logicalDevice, imageView);
}
