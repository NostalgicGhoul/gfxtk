#include <gfxtk/log.hpp>
#include "CommandBuffer.hpp"

void gfxtk::backend::CommandBuffer::beginCommandBuffer() {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(vulkanCommandBuffer, &beginInfo) != VK_SUCCESS) {
        // TODO: I want to implement a better error system than just aborting on failures within the render loop
        //       I think the best solution is just to return a type that can be easily checked as maybe
        //       `beginCommandBuffer == gfxtk::Success` or something. Idk, for this call it really isn't a huge deal as
        //       the only error really isn't recoverable and should instead be pre-emptively checked for.
        GFXTK_LOG_F("failed to begin recording command buffer on Vulkan backend!");
    }
}
