#include <gfxtk/log.hpp>
#include "TextureLayout.hpp"

VkImageLayout gfxtk::backend::TextureLayout::convert(gfxtk::TextureLayout textureLayout) {
    switch (textureLayout) {
        case gfxtk::TextureLayout::Undefined:
            return VK_IMAGE_LAYOUT_UNDEFINED;
        case gfxtk::TextureLayout::General:
            return VK_IMAGE_LAYOUT_GENERAL;
        case gfxtk::TextureLayout::ColorAttachment:
            return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        case gfxtk::TextureLayout::DepthStencilAttachment:
            return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        case gfxtk::TextureLayout::DepthStencilReadOnly:
            return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        case gfxtk::TextureLayout::ShaderReadOnly:
            return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        case gfxtk::TextureLayout::TransferSource:
            return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        case gfxtk::TextureLayout::TransferDestination:
            return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        case gfxtk::TextureLayout::PresentSource:
            return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        default:
            GFXTK_LOG_F("unknown `TextureLayout` found in `gfxtk::backend::TextureLayout::convert`!");
    }
}
