#ifndef GFXTK_BACKEND_VULKAN_MEMORYUSAGE_HPP
#define GFXTK_BACKEND_VULKAN_MEMORYUSAGE_HPP

#include <vk_mem_alloc.h>
#include <gfxtk/MemoryUsage.hpp>

namespace gfxtk::backend {
    struct MemoryUsage {
        static VmaMemoryUsage convert(gfxtk::MemoryUsage memoryUsage);

    };
}

#endif //GFXTK_BACKEND_VULKAN_MEMORYUSAGE_HPP
