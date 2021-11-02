#ifndef GFXTK_BACKEND_VULKAN_BUFFER_HPP
#define GFXTK_BACKEND_VULKAN_BUFFER_HPP

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include <memory>
#include <gfxtk/MemoryUsage.hpp>
#include <gfxtk/BufferUsageFlags.hpp>
#include "Device.hpp"

namespace gfxtk::backend {
    struct Buffer {
        static std::shared_ptr<Buffer> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                size_t size,
                gfxtk::BufferUsageFlags bufferUsageFlags,
                gfxtk::MemoryUsage memoryUsage
        );

        VmaAllocator vulkanMemoryAllocator;
        VmaAllocation vulkanMemoryAllocation;
        VkBuffer vulkanBuffer;

        Buffer(
                VmaAllocator vulkanMemoryAllocator,
                VmaAllocation vulkanMemoryAllocation,
                VkBuffer vulkanBuffer
        ) : vulkanMemoryAllocator(vulkanMemoryAllocator),
            vulkanMemoryAllocation(vulkanMemoryAllocation),
            vulkanBuffer(vulkanBuffer) {}
        ~Buffer();

        void* map();
        void unmap();

    };
}

#endif //GFXTK_BACKEND_VULKAN_BUFFER_HPP
