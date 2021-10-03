#ifndef GFXTK_BACKEND_VULKAN_DEVICE_HPP
#define GFXTK_BACKEND_VULKAN_DEVICE_HPP

#include <vulkan/vulkan.h>

namespace gfxtk::backend {
    struct Device {
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;

    };
}

#endif //GFXTK_BACKEND_VULKAN_DEVICE_HPP
