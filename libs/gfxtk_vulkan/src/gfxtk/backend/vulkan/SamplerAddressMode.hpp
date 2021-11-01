#ifndef GFXTK_BACKEND_VULKAN_SAMPLERADDRESSMODE_HPP
#define GFXTK_BACKEND_VULKAN_SAMPLERADDRESSMODE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/SamplerAddressMode.hpp>

namespace gfxtk::backend {
    struct SamplerAddressMode {
        static VkSamplerAddressMode convert(gfxtk::SamplerAddressMode samplerAddressMode);

    };
}

#endif //GFXTK_BACKEND_VULKAN_SAMPLERADDRESSMODE_HPP
