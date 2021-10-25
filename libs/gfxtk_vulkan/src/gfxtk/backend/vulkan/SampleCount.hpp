#ifndef GFXTK_BACKEND_VULKAN_SAMPLECOUNT_HPP
#define GFXTK_BACKEND_VULKAN_SAMPLECOUNT_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/SampleCount.hpp>

namespace gfxtk::backend {
    struct SampleCount {
        static VkSampleCountFlagBits convert(gfxtk::SampleCount sampleCount);

    };
}

#endif //GFXTK_BACKEND_VULKAN_SAMPLECOUNT_HPP
