#ifndef GFXTK_BACKEND_VULKAN_STENCILOP_HPP
#define GFXTK_BACKEND_VULKAN_STENCILOP_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/StencilOp.hpp>

namespace gfxtk::backend {
    struct StencilOp {
        static VkStencilOp convert(gfxtk::StencilOp stencilOp);

    };
}

#endif //GFXTK_BACKEND_VULKAN_STENCILOP_HPP
