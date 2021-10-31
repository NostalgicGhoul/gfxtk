#include <gfxtk/log.hpp>
#include "BindGroupLayout.hpp"
#include "ShaderStageFlags.hpp"
#include "BindGroupLayoutEntry.hpp"

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
        entryBinding.descriptorType = backend::BindGroupLayoutEntry::getDescriptorType(entry);
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

    return std::make_shared<BindGroupLayout>(backendDevice->logicalDevice, result, descriptor.entries);
}
