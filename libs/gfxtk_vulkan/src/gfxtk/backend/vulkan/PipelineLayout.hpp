#ifndef GFXTK_BACKEND_VULKAN_PIPELINELAYOUT_HPP
#define GFXTK_BACKEND_VULKAN_PIPELINELAYOUT_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include "Device.hpp"
#include "BindGroupLayout.hpp"

namespace gfxtk::backend {
    struct PipelineLayout {
        static std::shared_ptr<PipelineLayout> create(
                std::shared_ptr<backend::Device> const& device,
                std::vector<backend::BindGroupLayout*> const& bindingGroupLayouts
        );

        VkDevice vulkanDevice;
        VkPipelineLayout vulkanPipelineLayout;

        PipelineLayout(VkDevice vulkanDevice, VkPipelineLayout vulkanPipelineLayout)
                : vulkanDevice(vulkanDevice), vulkanPipelineLayout(vulkanPipelineLayout) {}
        ~PipelineLayout();

    };
}

#endif //GFXTK_BACKEND_VULKAN_PIPELINELAYOUT_HPP
