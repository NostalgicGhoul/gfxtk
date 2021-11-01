#include "TextureUsage.hpp"

VkImageUsageFlags gfxtk::backend::TextureUsage::convert(gfxtk::TextureUsage textureUsage) {
    VkImageUsageFlags result = 0;

    if ((textureUsage & gfxtk::TextureUsage::Sampled) == gfxtk::TextureUsage::Sampled) {
        result |= VK_IMAGE_USAGE_SAMPLED_BIT;
    }

    if ((textureUsage & gfxtk::TextureUsage::Storage) == gfxtk::TextureUsage::Storage) {
        result |= VK_IMAGE_USAGE_STORAGE_BIT;
    }

    if ((textureUsage & gfxtk::TextureUsage::TransferSource) == gfxtk::TextureUsage::TransferSource) {
        result |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    }

    if ((textureUsage & gfxtk::TextureUsage::TransferDestination) == gfxtk::TextureUsage::TransferDestination) {
        result |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    }

    if ((textureUsage & gfxtk::TextureUsage::ColorAttachment) == gfxtk::TextureUsage::ColorAttachment) {
        result |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    }

    if ((textureUsage & gfxtk::TextureUsage::DepthStencilAttachment) == gfxtk::TextureUsage::DepthStencilAttachment) {
        result |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    }

    if ((textureUsage & gfxtk::TextureUsage::InputAttachment) == gfxtk::TextureUsage::InputAttachment) {
        result |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
    }

    return result;
}
