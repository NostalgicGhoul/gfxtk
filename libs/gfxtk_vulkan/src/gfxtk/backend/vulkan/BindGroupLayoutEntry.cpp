#include <gfxtk/log.hpp>
#include "BindGroupLayoutEntry.hpp"

VkDescriptorType gfxtk::backend::BindGroupLayoutEntry::getDescriptorType(gfxtk::BindGroupLayoutEntry const& entry) {
    switch (entry.bindingType()) {
        case gfxtk::BindingLayoutType::Buffer:
            switch (entry.buffer().type) {
                case gfxtk::BufferBindingType::Uniform:
                    return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                case gfxtk::BufferBindingType::Storage:
                case gfxtk::BufferBindingType::ReadOnlyStorage:
                    return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                default:
                GFXTK_LOG_F("unknown `BufferBindingType` passed to `gfxtk::backend::BindGroupLayoutEntry::getDescriptorType`!");
            }
        case gfxtk::BindingLayoutType::Sampler:
            return VK_DESCRIPTOR_TYPE_SAMPLER;
        case gfxtk::BindingLayoutType::CombinedTextureSampler:
            return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        case gfxtk::BindingLayoutType::Texture:
            return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        case gfxtk::BindingLayoutType::StorageTexture:
            return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        default:
        GFXTK_LOG_F("unknown `BindingLayoutType` passed to `gfxtk::backend::BindGroupLayoutEntry::getDescriptorType`!");
    }
}
