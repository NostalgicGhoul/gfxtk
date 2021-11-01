#ifndef GFXTK_BACKEND_VULKAN_TEXTURE_HPP
#define GFXTK_BACKEND_VULKAN_TEXTURE_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <vk_mem_alloc.h>
#include <gfxtk/Extent3D.hpp>
#include <gfxtk/TextureType.hpp>
#include <gfxtk/TextureUsage.hpp>
#include <gfxtk/MemoryUsage.hpp>
#include "Device.hpp"
#include "TextureLayout.hpp"

namespace gfxtk::backend {
    struct Texture {
        static std::shared_ptr<Texture> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                gfxtk::TextureType type,
                gfxtk::PixelFormat format,
                gfxtk::Extent3D extent,
                uint32_t mipLevels,
                uint32_t arrayLayers,
                gfxtk::TextureUsage usage,
                gfxtk::MemoryUsage memoryUsage
        );

        VmaAllocator vulkanMemoryAllocator;
        VmaAllocation vulkanMemoryAllocation;
        VkImage vulkanImage;

        Texture(VmaAllocator vulkanMemoryAllocator, VmaAllocation vulkanMemoryAllocation, VkImage vulkanImage)
                : vulkanMemoryAllocator(vulkanMemoryAllocator),
                  vulkanMemoryAllocation(vulkanMemoryAllocation),
                  vulkanImage(vulkanImage) {}
        ~Texture() {
            vmaDestroyImage(vulkanMemoryAllocator, vulkanImage, vulkanMemoryAllocation);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTURE_HPP
