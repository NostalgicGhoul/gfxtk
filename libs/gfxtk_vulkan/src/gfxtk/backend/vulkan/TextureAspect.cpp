#include "TextureAspect.hpp"

VkImageAspectFlags gfxtk::backend::TextureAspect::convert(gfxtk::TextureAspect textureAspect) {
    VkImageAspectFlags result = 0;

    if ((textureAspect & gfxtk::TextureAspect::ColorOnly) == gfxtk::TextureAspect::ColorOnly) {
        result |= VK_IMAGE_ASPECT_COLOR_BIT;
    }

    if ((textureAspect & gfxtk::TextureAspect::DepthOnly) == gfxtk::TextureAspect::DepthOnly) {
        result |= VK_IMAGE_ASPECT_DEPTH_BIT;
    }

    if ((textureAspect & gfxtk::TextureAspect::StencilOnly) == gfxtk::TextureAspect::StencilOnly) {
        result |= VK_IMAGE_ASPECT_STENCIL_BIT;
    }

    return result;
}
