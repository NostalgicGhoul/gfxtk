#ifndef GFXTK_BACKEND_VULKAN_SAMPLER_HPP
#define GFXTK_BACKEND_VULKAN_SAMPLER_HPP

#include <vulkan/vulkan.h>

namespace gfxtk::backend {
    struct Sampler {
        VkSampler vulkanSampler;

    };
}

#endif //GFXTK_BACKEND_VULKAN_SAMPLER_HPP
