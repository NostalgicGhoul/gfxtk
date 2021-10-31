#ifndef GFXTK_BACKEND_VULKAN_BINDGROUP_HPP
#define GFXTK_BACKEND_VULKAN_BINDGROUP_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include "BindGroupLayout.hpp"
#include "BindGroupEntry.hpp"

namespace gfxtk::backend {
    struct BindGroupPool {
        VkDevice vulkanDevice;
        VkDescriptorPool vulkanDescriptorPool;

        BindGroupPool(VkDevice vulkanDevice, VkDescriptorPool vulkanDescriptorPool)
                : vulkanDevice(vulkanDevice), vulkanDescriptorPool(vulkanDescriptorPool) {}

        ~BindGroupPool() {
            vkDestroyDescriptorPool(vulkanDevice, vulkanDescriptorPool, nullptr);
        }

    };

    struct BindGroup {
        static std::vector<std::shared_ptr<BindGroup>> createBindGroups(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::shared_ptr<backend::BindGroupLayout> const& backendBindGroupLayout,
                std::vector<std::vector<BindGroupEntry*>> const& groupEntries
        );

        std::shared_ptr<BindGroupPool> bindGroupPool;
        VkDescriptorSet vulkanDescriptorSet;

        BindGroup(std::shared_ptr<BindGroupPool> bindGroupPool, VkDescriptorSet vulkanDescriptorSet)
                : bindGroupPool(std::move(bindGroupPool)), vulkanDescriptorSet(vulkanDescriptorSet) {}

    };
}

#endif //GFXTK_BACKEND_VULKAN_BINDGROUP_HPP
