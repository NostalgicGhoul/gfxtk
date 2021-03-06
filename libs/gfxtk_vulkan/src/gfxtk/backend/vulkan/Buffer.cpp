#include <gfxtk/log.hpp>
#include "Buffer.hpp"
#include "BufferUsageFlags.hpp"
#include "MemoryUsage.hpp"

std::shared_ptr<gfxtk::backend::Buffer> gfxtk::backend::Buffer::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        size_t size,
        gfxtk::BufferUsageFlags bufferUsageFlags,
        gfxtk::MemoryUsage memoryUsage
) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = backend::BufferUsageFlags::convert(bufferUsageFlags);

    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = backend::MemoryUsage::convert(memoryUsage);

    VkBuffer buffer;
    VmaAllocation allocation;

    if (vmaCreateBuffer(backendDevice->allocator, &bufferInfo, &allocInfo, &buffer, &allocation, nullptr)
            != VK_SUCCESS) {
        GFXTK_LOG_F("failed to allocate Buffer on Vulkan backend!");
    }

    return std::make_shared<Buffer>(backendDevice->allocator, allocation, buffer);
}

gfxtk::backend::Buffer::~Buffer() {
    vmaDestroyBuffer(vulkanMemoryAllocator, vulkanBuffer, vulkanMemoryAllocation);
}

void* gfxtk::backend::Buffer::map() {
    void* mappedData;
    vmaMapMemory(vulkanMemoryAllocator, vulkanMemoryAllocation, &mappedData);
    return mappedData;
}

void gfxtk::backend::Buffer::unmap() {
    vmaUnmapMemory(vulkanMemoryAllocator, vulkanMemoryAllocation);
    vmaFlushAllocation(vulkanMemoryAllocator, vulkanMemoryAllocation, 0, VK_WHOLE_SIZE);
}
