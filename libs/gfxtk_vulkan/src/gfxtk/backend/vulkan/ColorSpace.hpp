#ifndef GFXTK_BACKEND_VULKAN_COLORSPACE_HPP
#define GFXTK_BACKEND_VULKAN_COLORSPACE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/ColorSpace.hpp>

namespace gfxtk::backend {
    struct ColorSpace {
        static VkColorSpaceKHR convertToVkColorSpaceKHR(gfxtk::ColorSpace colorSpace);

    };
}

#endif //GFXTK_BACKEND_VULKAN_COLORSPACE_HPP
