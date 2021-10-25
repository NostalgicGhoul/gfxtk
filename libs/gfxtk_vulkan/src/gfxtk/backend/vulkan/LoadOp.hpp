#ifndef GFXTK_BACKEND_VULKAN_LOADOP_HPP
#define GFXTK_BACKEND_VULKAN_LOADOP_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/LoadOp.hpp>

namespace gfxtk::backend {
    struct LoadOp {
        static VkAttachmentLoadOp convert(gfxtk::LoadOp loadOp);

    };
}

#endif //GFXTK_BACKEND_VULKAN_LOADOP_HPP
