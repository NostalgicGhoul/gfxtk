#ifndef GFXTK_BACKEND_VULKAN_SAMPLERFILTER_HPP
#define GFXTK_BACKEND_VULKAN_SAMPLERFILTER_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/SamplerFilter.hpp>

namespace gfxtk::backend {
    struct SamplerFilter {
        static VkFilter convert(gfxtk::SamplerFilter samplerFilter);

    };
}

#endif //GFXTK_BACKEND_VULKAN_SAMPLERFILTER_HPP
