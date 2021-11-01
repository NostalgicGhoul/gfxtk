#include "AccessFlags.hpp"

VkAccessFlags gfxtk::backend::AccessFlags::convert(gfxtk::AccessFlags accessFlags) {
    VkAccessFlags result = 0;

    if ((accessFlags & gfxtk::AccessFlags::ShaderRead) == gfxtk::AccessFlags::ShaderRead) {
        result |= VK_ACCESS_SHADER_READ_BIT;
    }

    if ((accessFlags & gfxtk::AccessFlags::ShaderWrite) == gfxtk::AccessFlags::ShaderWrite) {
        result |= VK_ACCESS_SHADER_WRITE_BIT;
    }

    if ((accessFlags & gfxtk::AccessFlags::ColorAttachmentRead) == gfxtk::AccessFlags::ColorAttachmentRead) {
        result |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
    }

    if ((accessFlags & gfxtk::AccessFlags::ColorAttachmentWrite) == gfxtk::AccessFlags::ColorAttachmentWrite) {
        result |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    }

    if ((accessFlags & gfxtk::AccessFlags::DepthStencilAttachmentRead) == gfxtk::AccessFlags::DepthStencilAttachmentRead) {
        result |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
    }

    if ((accessFlags & gfxtk::AccessFlags::DepthStencilAttachmentWrite) == gfxtk::AccessFlags::DepthStencilAttachmentWrite) {
        result |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    }

    if ((accessFlags & gfxtk::AccessFlags::TransferRead) == gfxtk::AccessFlags::TransferRead) {
        result |= VK_ACCESS_TRANSFER_READ_BIT;
    }

    if ((accessFlags & gfxtk::AccessFlags::TransferWrite) == gfxtk::AccessFlags::TransferWrite) {
        result |= VK_ACCESS_TRANSFER_WRITE_BIT;
    }

    return result;
}
