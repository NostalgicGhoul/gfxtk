#ifndef GFXTK_BACKEND_VULKAN_BUFFERUSAGEFLAGS_HPP
#define GFXTK_BACKEND_VULKAN_BUFFERUSAGEFLAGS_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/BufferUsageFlags.hpp>

namespace gfxtk::backend {
    struct BufferUsageFlags {
        static VkBufferUsageFlags convert(gfxtk::BufferUsageFlags bufferUsageFlags);

    };
}

#endif //GFXTK_BACKEND_VULKAN_BUFFERUSAGEFLAGS_HPP
