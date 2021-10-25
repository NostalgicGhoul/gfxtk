#ifndef GFXTK_BACKEND_VULKAN_COLORWRITEMASK_HPP
#define GFXTK_BACKEND_VULKAN_COLORWRITEMASK_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/ColorWriteMask.hpp>

namespace gfxtk::backend {
    struct ColorWriteMask {
        static VkColorComponentFlags convert(gfxtk::ColorWriteMask colorWriteMask);

    };
}

#endif //GFXTK_BACKEND_VULKAN_COLORWRITEMASK_HPP
