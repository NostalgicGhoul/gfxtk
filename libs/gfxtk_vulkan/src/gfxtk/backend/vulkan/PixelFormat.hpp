#ifndef GFXTK_BACKEND_VULKAN_PIXELFORMAT_HPP
#define GFXTK_BACKEND_VULKAN_PIXELFORMAT_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/PixelFormat.hpp>

namespace gfxtk::backend {
    struct PixelFormat {
        static VkFormat convertToVkFormat(gfxtk::PixelFormat pixelFormat);

    };
}

#endif //GFXTK_BACKEND_VULKAN_PIXELFORMAT_HPP
