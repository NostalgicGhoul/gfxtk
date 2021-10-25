#ifndef GFXTK_BACKEND_VULKAN_COMPAREOP_HPP
#define GFXTK_BACKEND_VULKAN_COMPAREOP_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/CompareOp.hpp>

namespace gfxtk::backend {
    struct CompareOp {
        static VkCompareOp convert(gfxtk::CompareOp compareOp);

    };
}

#endif //GFXTK_BACKEND_VULKAN_COMPAREOP_HPP
