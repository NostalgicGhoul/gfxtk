#ifndef GFXTK_BACKEND_VULKAN_BLENDOP_HPP
#define GFXTK_BACKEND_VULKAN_BLENDOP_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/BlendOp.hpp>

namespace gfxtk::backend {
    struct BlendOp {
        static VkBlendOp convert(gfxtk::BlendOp blendOp);

    };
}

#endif //GFXTK_BACKEND_VULKAN_BLENDOP_HPP
