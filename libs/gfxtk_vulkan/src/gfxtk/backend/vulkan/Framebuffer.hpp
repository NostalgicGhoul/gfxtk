#ifndef GFXTK_BACKEND_VULKAN_FRAMEBUFFER_HPP
#define GFXTK_BACKEND_VULKAN_FRAMEBUFFER_HPP

#include <vulkan/vulkan.h>

namespace gfxtk::backend {
    struct Framebuffer {
        VkFramebuffer vulkanFramebuffer;
        uint32_t currentImageIndex;

        Framebuffer(VkFramebuffer vulkanFramebuffer, uint32_t currentImageIndex)
                : vulkanFramebuffer(vulkanFramebuffer), currentImageIndex(currentImageIndex) {}

    };
}

#endif //GFXTK_BACKEND_VULKAN_FRAMEBUFFER_HPP
