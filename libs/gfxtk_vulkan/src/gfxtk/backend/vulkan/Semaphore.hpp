#ifndef GFXTK_BACKEND_VULKAN_SEMAPHORE_HPP
#define GFXTK_BACKEND_VULKAN_SEMAPHORE_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include "Device.hpp"

namespace gfxtk::backend {
    struct Semaphore {
        static std::shared_ptr<Semaphore> create(std::shared_ptr<backend::Device> const& backendDevice);

        VkDevice vulkanDevice;
        VkSemaphore vulkanSemaphore;

        Semaphore(VkDevice vulkanDevice, VkSemaphore vulkanSemaphore)
                : vulkanDevice(vulkanDevice), vulkanSemaphore(vulkanSemaphore) {}
        ~Semaphore() {
            vkDestroySemaphore(vulkanDevice, vulkanSemaphore, nullptr);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_SEMAPHORE_HPP
