#ifndef GFXTK_BACKEND_VULKAN_TEXTUREVIEWTYPE_HPP
#define GFXTK_BACKEND_VULKAN_TEXTUREVIEWTYPE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/TextureViewType.hpp>

namespace gfxtk::backend {
    struct TextureViewType {
        static VkImageViewType convert(gfxtk::TextureViewType textureViewType);

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTUREVIEWTYPE_HPP
