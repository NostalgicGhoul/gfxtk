#ifndef GFXTK_BACKEND_VULKAN_BLENDFACTOR_HPP
#define GFXTK_BACKEND_VULKAN_BLENDFACTOR_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/BlendFactor.hpp>

namespace gfxtk::backend {
    struct BlendFactor {
        static VkBlendFactor convert(gfxtk::BlendFactor blendFactor);

    };
}

#endif //GFXTK_BLENDFACTOR_HPP
