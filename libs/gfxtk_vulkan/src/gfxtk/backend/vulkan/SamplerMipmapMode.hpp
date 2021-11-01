#ifndef GFXTK_BACKEND_VULKAN_SAMPLERMIPMAPMODE_HPP
#define GFXTK_BACKEND_VULKAN_SAMPLERMIPMAPMODE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/SamplerMipmapMode.hpp>

namespace gfxtk::backend {
    struct SamplerMipmapMode {
        static VkSamplerMipmapMode convert(gfxtk::SamplerMipmapMode samplerMipmapMode);

    };
}

#endif //GFXTK_BACKEND_VULKAN_SAMPLERMIPMAPMODE_HPP
