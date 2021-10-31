#include <gfxtk/log.hpp>
#include "BindGroup.hpp"
#include "BindGroupLayoutEntry.hpp"

std::vector<std::shared_ptr<gfxtk::backend::BindGroup>> gfxtk::backend::BindGroup::createBindGroups(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::shared_ptr<backend::BindGroupLayout> const& backendBindGroupLayout,
        std::vector<std::vector<BindGroupEntry*>> const& groupEntries
) {
    // TODO: This should be the types found in `layout` multiplied by the size of `groupEntries`
    //       The index of `groupEntries` should match the `layout`
    std::vector<VkDescriptorPoolSize> poolSizes;

    for (auto const& layoutEntry : backendBindGroupLayout->entries) {
        auto vulkanDescriptorType = backend::BindGroupLayoutEntry::getDescriptorType(layoutEntry);
        bool poolSizeFound = false;

        for (auto& poolSize : poolSizes) {
            if (poolSize.type == vulkanDescriptorType) {
                poolSizeFound = true;
                // Rather than multiplying by the number of frames, I just use it as the increment.
                poolSize.descriptorCount += groupEntries.size();
                break;
            }
        }

        if (!poolSizeFound) {
            VkDescriptorPoolSize newPoolSize{};
            newPoolSize.type = vulkanDescriptorType;
            newPoolSize.descriptorCount = groupEntries.size();
            poolSizes.push_back(newPoolSize);
        }
    }

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(groupEntries.size());

    VkDescriptorPool vulkanDescriptorPool;

    if (vkCreateDescriptorPool(backendDevice->logicalDevice, &poolInfo, nullptr, &vulkanDescriptorPool) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create new `VkDescriptorPool` required by `BindGroup` on Vulkan backend!");
    }

    std::vector<VkDescriptorSetLayout> layouts(groupEntries.size(), backendBindGroupLayout->vulkanDescriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = vulkanDescriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(groupEntries.size());
    allocInfo.pSetLayouts = layouts.data();

    std::vector<VkDescriptorSet> vulkanDescriptorSets;
    vulkanDescriptorSets.resize(groupEntries.size());
    if (vkAllocateDescriptorSets(backendDevice->logicalDevice, &allocInfo, vulkanDescriptorSets.data()) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to allocate descriptor sets required by `BindGroup` on Vulkan backend!");
    }

    for (size_t i = 0; i < groupEntries.size(); i++) {
        for (size_t j = 0; j < groupEntries[i].size(); ++j) {
            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = vulkanDescriptorSets[i];
            descriptorWrite.dstBinding = backendBindGroupLayout->entries[j].binding;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType =
                    backend::BindGroupLayoutEntry::getDescriptorType(backendBindGroupLayout->entries[j]);
            descriptorWrite.descriptorCount = 1;

            VkDescriptorBufferInfo bufferInfo{};
            VkDescriptorImageInfo imageInfo{};

            switch (groupEntries[i][j]->bindingType()) {
                case BindingType::Buffer:
                    bufferInfo.buffer = groupEntries[i][j]->getBuffer()->vulkanBuffer;
                    bufferInfo.offset = groupEntries[i][j]->getBufferOffset();
                    bufferInfo.range = groupEntries[i][j]->getBufferSize();
                    descriptorWrite.pBufferInfo = &bufferInfo;
                    break;
                case BindingType::Sampler:
                    imageInfo.sampler = groupEntries[i][j]->getSampler()->vulkanSampler;
                    break;
                case BindingType::TextureView:
                    imageInfo.imageView = groupEntries[i][j]->getTextureView()->vulkanImageView;
                    imageInfo.imageLayout = backend::TextureLayout::convert(groupEntries[i][j]->getTextureLayout());
                    break;
            }

            vkUpdateDescriptorSets(backendDevice->logicalDevice, 1, &descriptorWrite, 0, nullptr);
        }
    }

    std::shared_ptr<BindGroupPool> bindGroupPool =
            std::make_shared<BindGroupPool>(backendDevice->logicalDevice, vulkanDescriptorPool);
    std::vector<std::shared_ptr<backend::BindGroup>> results;
    results.reserve(groupEntries.size());

    for (auto& descriptorSet : vulkanDescriptorSets) {
        results.push_back(std::make_shared<BindGroup>(bindGroupPool, descriptorSet));
    }

    return results;
}
