#ifndef GFXTK_BACKEND_VULKAN_TEXTUREASPECT_HPP
#define GFXTK_BACKEND_VULKAN_TEXTUREASPECT_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/TextureAspect.hpp>

namespace gfxtk::backend {
    struct TextureAspect {
        static VkImageAspectFlags convert(gfxtk::TextureAspect textureAspect);

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTUREASPECT_HPP
