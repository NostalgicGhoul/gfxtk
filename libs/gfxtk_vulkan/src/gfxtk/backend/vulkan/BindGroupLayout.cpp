#include <gfxtk/log.hpp>
#include "BindGroupLayout.hpp"
#include "ShaderStageFlags.hpp"

VkDescriptorType gfxtk_backend_vulkan_getDescriptorType(gfxtk::BindGroupLayoutEntry const& entry) {
    switch (entry.bindingType()) {
        case gfxtk::BindingLayoutType::Buffer:
            switch (entry.buffer().type) {
                case gfxtk::BufferBindingType::Uniform:
                    return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                case gfxtk::BufferBindingType::Storage:
                case gfxtk::BufferBindingType::ReadOnlyStorage:
                    return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                default:
                    GFXTK_LOG_F("unknown `BufferBindingType` passed to `gfxtk_backend_vulkan_getDescriptorType`!");
            }
        case gfxtk::BindingLayoutType::Sampler:
            return VK_DESCRIPTOR_TYPE_SAMPLER;
        case gfxtk::BindingLayoutType::Texture:
            return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        case gfxtk::BindingLayoutType::StorageTexture:
            return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        default:
            GFXTK_LOG_F("unknown `BindingLayoutType` passed to `gfxtk_backend_vulkan_getDescriptorType`!");
    }
}

std::shared_ptr<gfxtk::backend::BindGroupLayout> gfxtk::backend::BindGroupLayout::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        gfxtk::BindGroupLayoutDescriptor const& descriptor
) {
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    bindings.reserve(descriptor.entries.size());

    for (auto const& entry : descriptor.entries) {
        VkDescriptorSetLayoutBinding entryBinding{};
        entryBinding.binding = entry.binding;
        entryBinding.descriptorCount = 1;
        entryBinding.descriptorType = gfxtk_backend_vulkan_getDescriptorType(entry);
        entryBinding.pImmutableSamplers = nullptr;
        entryBinding.stageFlags = gfxtk::backend::ShaderStageFlags::convertToVkShaderStageFlags(entry.shaderStages);
        bindings.push_back(entryBinding);
    }

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    VkDescriptorSetLayout result;

    if (vkCreateDescriptorSetLayout(backendDevice->logicalDevice, &layoutInfo, nullptr, &result) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create `BindGroupLayout` for `Vulkan` backend!");
    }

    return std::make_shared<BindGroupLayout>(backendDevice->logicalDevice, result);
}

gfxtk::backend::BindGroupLayout::~BindGroupLayout() {
    vkDestroyDescriptorSetLayout(vulkanDevice, vulkanDescriptorSetLayout, nullptr);
}

gfxtk::backend::BindGroupLayout::BindGroupLayout(
        VkDevice vulkanDevice,
        VkDescriptorSetLayout vulkanDescriptorSetLayout
) : vulkanDevice(vulkanDevice), vulkanDescriptorSetLayout(vulkanDescriptorSetLayout) {}
