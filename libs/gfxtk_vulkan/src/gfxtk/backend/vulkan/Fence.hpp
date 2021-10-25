#ifndef GFXTK_BACKEND_VULKAN_FENCE_HPP
#define GFXTK_BACKEND_VULKAN_FENCE_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include "Device.hpp"

namespace gfxtk::backend {
    struct Fence {
        static std::shared_ptr<backend::Fence> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                bool signaled
        );

        VkDevice vulkanDevice;
        VkFence vulkanFence;

        Fence(VkDevice vulkanDevice, VkFence vulkanFence)
                : vulkanDevice(vulkanDevice), vulkanFence(vulkanFence) {}
        ~Fence() {
            vkDestroyFence(vulkanDevice, vulkanFence, nullptr);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_FENCE_HPP
