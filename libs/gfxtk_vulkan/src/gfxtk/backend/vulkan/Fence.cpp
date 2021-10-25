#include <gfxtk/log.hpp>
#include "Fence.hpp"

std::shared_ptr<gfxtk::backend::Fence> gfxtk::backend::Fence::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        bool signaled
) {
    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

    if (signaled) {
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    }

    VkFence vulkanFence;

    if (vkCreateFence(backendDevice->logicalDevice, &fenceInfo, nullptr, &vulkanFence) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create Fence on Vulkan backend!");
    }

    return std::make_shared<backend::Fence>(backendDevice->logicalDevice, vulkanFence);
}
