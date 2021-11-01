#include <gfxtk/log.hpp>
#include "Texture.hpp"
#include "TextureType.hpp"
#include "PixelFormat.hpp"
#include "TextureUsage.hpp"
#include "MemoryUsage.hpp"

std::shared_ptr<gfxtk::backend::Texture> gfxtk::backend::Texture::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        gfxtk::TextureType type,
        gfxtk::PixelFormat format,
        gfxtk::Extent3D extent,
        uint32_t mipLevels,
        uint32_t arrayLayers,
        gfxtk::TextureUsage usage,
        gfxtk::MemoryUsage memoryUsage
) {
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = backend::TextureType::convert(type);
    imageInfo.format = backend::PixelFormat::convert(format);
    imageInfo.extent.width = extent.width;
    imageInfo.extent.height = extent.height;
    imageInfo.extent.depth = extent.depth;
    imageInfo.mipLevels = mipLevels;
    imageInfo.arrayLayers = arrayLayers;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.usage = backend::TextureUsage::convert(usage);
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.flags = 0;

    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = backend::MemoryUsage::convert(memoryUsage);

    VkImage resultImage;
    VmaAllocation resultAllocation;
    if (vmaCreateImage(backendDevice->allocator, &imageInfo, &allocInfo, &resultImage, &resultAllocation, nullptr)
            != VK_SUCCESS) {
        GFXTK_LOG_F("failed to allocate Texture on Vulkan backend!");
    }

    return std::make_shared<Texture>(backendDevice->allocator, resultAllocation, resultImage);
}
