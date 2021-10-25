#include "PipelineLayout.hpp"
#include <gfxtk/log.hpp>

std::shared_ptr<gfxtk::backend::PipelineLayout> gfxtk::backend::PipelineLayout::create(
        std::shared_ptr<backend::Device> const& device,
        std::vector<backend::BindGroupLayout*> const& bindingGroupLayouts
) {
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    descriptorSetLayouts.reserve(bindingGroupLayouts.size());

    for (auto const& bindingGroupLayout : bindingGroupLayouts) {
        descriptorSetLayouts.push_back(bindingGroupLayout->vulkanDescriptorSetLayout);
    }

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();

    VkPipelineLayout result{};

    if (vkCreatePipelineLayout(device->logicalDevice, &pipelineLayoutInfo, nullptr, &result) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create a `PipelineLayout` for `Vulkan` backend!");
    }

    return std::make_shared<PipelineLayout>(device->logicalDevice, result);
}

gfxtk::backend::PipelineLayout::~PipelineLayout() {
    vkDestroyPipelineLayout(vulkanDevice, vulkanPipelineLayout, nullptr);
}
