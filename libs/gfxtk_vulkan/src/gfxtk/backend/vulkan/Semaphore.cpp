#include <gfxtk/log.hpp>
#include "Semaphore.hpp"

std::shared_ptr<gfxtk::backend::Semaphore> gfxtk::backend::Semaphore::create(
        std::shared_ptr<backend::Device> const& backendDevice
) {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkSemaphore vulkanSemaphore;

    if (vkCreateSemaphore(backendDevice->logicalDevice, &semaphoreInfo, nullptr, &vulkanSemaphore) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create Semaphore on Vulkan backend!");
    }

    return std::make_shared<Semaphore>(backendDevice->logicalDevice, vulkanSemaphore);
}
