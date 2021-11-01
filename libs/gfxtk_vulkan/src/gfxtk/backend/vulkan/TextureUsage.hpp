#ifndef GFXTK_BACKEND_VULKAN_TEXTUREUSAGE_HPP
#define GFXTK_BACKEND_VULKAN_TEXTUREUSAGE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/TextureUsage.hpp>

namespace gfxtk::backend {
    struct TextureUsage {
        static VkImageUsageFlags convert(gfxtk::TextureUsage textureUsage);

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTUREUSAGE_HPP
