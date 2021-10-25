#ifndef GFXTK_BACKEND_VULKAN_CULLMODE_HPP
#define GFXTK_BACKEND_VULKAN_CULLMODE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/CullMode.hpp>

namespace gfxtk::backend {
    struct CullMode {
        static VkCullModeFlags convert(gfxtk::CullMode cullMode);

    };
}

#endif //GFXTK_BACKEND_VULKAN_CULLMODE_HPP
