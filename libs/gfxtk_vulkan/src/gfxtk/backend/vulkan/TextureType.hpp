#ifndef GFXTK_BACKEND_VULKAN_TEXTURETYPE_HPP
#define GFXTK_BACKEND_VULKAN_TEXTURETYPE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/TextureType.hpp>

namespace gfxtk::backend {
    struct TextureType {
        static VkImageType convert(gfxtk::TextureType textureType);

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTURETYPE_HPP
