#include "BufferUsageFlags.hpp"

VkBufferUsageFlags gfxtk::backend::BufferUsageFlags::convert(gfxtk::BufferUsageFlags bufferUsageFlags) {
    VkBufferUsageFlags result = 0;

    if ((bufferUsageFlags & gfxtk::BufferUsageFlags::TransferSource) ==
            gfxtk::BufferUsageFlags::TransferSource) {
        result |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    }

    if ((bufferUsageFlags & gfxtk::BufferUsageFlags::TransferDestination) ==
            gfxtk::BufferUsageFlags::TransferDestination) {
        result |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    }

    if ((bufferUsageFlags & gfxtk::BufferUsageFlags::Uniform) ==
            gfxtk::BufferUsageFlags::Uniform) {
        result |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    }

    if ((bufferUsageFlags & gfxtk::BufferUsageFlags::Storage) ==
            gfxtk::BufferUsageFlags::Storage) {
        result |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    }

    if ((bufferUsageFlags & gfxtk::BufferUsageFlags::Index) ==
            gfxtk::BufferUsageFlags::Index) {
        result |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    }

    if ((bufferUsageFlags & gfxtk::BufferUsageFlags::Vertex) ==
            gfxtk::BufferUsageFlags::Vertex) {
        result |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    }

    if ((bufferUsageFlags & gfxtk::BufferUsageFlags::Indirect) ==
            gfxtk::BufferUsageFlags::Indirect) {
        result |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
    }

    return result;
}
