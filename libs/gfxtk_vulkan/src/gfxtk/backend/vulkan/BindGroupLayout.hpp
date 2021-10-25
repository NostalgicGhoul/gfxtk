#ifndef GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUT_HPP
#define GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUT_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/BindGroupLayoutDescriptor.hpp>
#include "Device.hpp"

namespace gfxtk::backend {
    struct BindGroupLayout {
        static std::shared_ptr<BindGroupLayout> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                BindGroupLayoutDescriptor const& descriptor
        );

        VkDevice vulkanDevice;
        VkDescriptorSetLayout vulkanDescriptorSetLayout;

        BindGroupLayout(VkDevice vulkanDevice, VkDescriptorSetLayout vulkanDescriptorSetLayout)
                : vulkanDevice(vulkanDevice), vulkanDescriptorSetLayout(vulkanDescriptorSetLayout) {}
        ~BindGroupLayout();

    };
}

#endif //GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUT_HPP
