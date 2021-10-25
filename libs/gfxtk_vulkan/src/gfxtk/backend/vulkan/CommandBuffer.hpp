#ifndef GFXTK_BACKEND_VULKAN_COMMANDBUFFER_HPP
#define GFXTK_BACKEND_VULKAN_COMMANDBUFFER_HPP

#include <vulkan/vulkan.h>

namespace gfxtk::backend {
    struct CommandBuffer {
        VkCommandBuffer vulkanCommandBuffer;

        explicit CommandBuffer(VkCommandBuffer vulkanCommandBuffer)
                : vulkanCommandBuffer(vulkanCommandBuffer) {}

        void beginCommandBuffer();

    };
}

#endif //GFXTK_BACKEND_VULKAN_COMMANDBUFFER_HPP
