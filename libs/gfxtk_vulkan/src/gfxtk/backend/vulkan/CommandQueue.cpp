#include <gfxtk/log.hpp>
#include "CommandQueue.hpp"
#include "PipelineStage.hpp"

std::shared_ptr<gfxtk::backend::CommandQueue> gfxtk::backend::CommandQueue::createRenderCommandQueue(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::shared_ptr<backend::SwapChain> const& swapChain,
        gfxtk::QueueFamily const& graphicsQueue
) {
    VkQueue vulkanQueue;
    vkGetDeviceQueue(backendDevice->logicalDevice, graphicsQueue.id(), 0, &vulkanQueue);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = graphicsQueue.id();
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    VkCommandPool commandPool;

    if (vkCreateCommandPool(backendDevice->logicalDevice, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create graphics command pool for Vulkan backend!");
    }

    std::vector<VkCommandBuffer> vulkanCommandBuffers;
    // NOTE: I'm setting the size to the number of image views rather than the number of framebuffers just in case
    //       someone attempts to create the command queue before setting the render pass for the swap chain
    vulkanCommandBuffers.resize(swapChain->vulkanSwapChainImageViews.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(vulkanCommandBuffers.size());

    if (vkAllocateCommandBuffers(backendDevice->logicalDevice, &allocInfo, vulkanCommandBuffers.data()) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to preload command encoders for Vulkan backend!");
    }

    return std::make_shared<gfxtk::backend::CommandQueue>(
            backendDevice->logicalDevice,
            vulkanQueue,
            commandPool,
            vulkanCommandBuffers
    );
}

std::unique_ptr<gfxtk::backend::CommandBuffer> gfxtk::backend::CommandQueue::getCommandBufferForFrame(
        std::unique_ptr<backend::Framebuffer> const& currentFramebuffer
) {
    // NOTE: It is impossible to destroy a `VkCommandBuffer` without destroying the whole `VkCommandPool` so this is
    //       safe to do, it won't destroy our command buffer.
    return std::make_unique<CommandBuffer>(vulkanCommandBuffers[currentFramebuffer->currentImageIndex]);
}

void gfxtk::backend::CommandQueue::submit(
        std::shared_ptr<backend::Semaphore> const& waitBackendSemaphore,
        gfxtk::PipelineStage waitPipelineStage,
        std::unique_ptr<backend::CommandBuffer> const& backendCommandBuffer,
        std::shared_ptr<backend::Semaphore> const& signalBackendSemaphore,
        std::shared_ptr<backend::Fence> const& backendFence
) {
    VkFence vulkanFence = VK_NULL_HANDLE;

    if (backendFence != nullptr) {
        vulkanFence = backendFence->vulkanFence;
    }

    VkSubmitInfo vulkanSubmitInfo{};
    vulkanSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkPipelineStageFlags waitStages[] = {backend::PipelineStage::convert(waitPipelineStage)};
    vulkanSubmitInfo.waitSemaphoreCount = 1;
    vulkanSubmitInfo.pWaitSemaphores = &waitBackendSemaphore->vulkanSemaphore;
    vulkanSubmitInfo.pWaitDstStageMask = waitStages;
    vulkanSubmitInfo.commandBufferCount = 1;
    vulkanSubmitInfo.pCommandBuffers = &backendCommandBuffer->vulkanCommandBuffer;
    vulkanSubmitInfo.signalSemaphoreCount = 1;
    vulkanSubmitInfo.pSignalSemaphores = &signalBackendSemaphore->vulkanSemaphore;

    if (vkQueueSubmit(vulkanQueue, 1, &vulkanSubmitInfo, vulkanFence) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to submit command buffer to queue on Vulkan backend!");
    }
}

gfxtk::PresentationErrors gfxtk::backend::CommandQueue::present(
        std::shared_ptr<backend::Semaphore> const& waitBackendSemaphore,
        std::shared_ptr<backend::SwapChain> const& backendSwapChain,
        std::unique_ptr<backend::Framebuffer> const& backendFramebuffer
) {
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &waitBackendSemaphore->vulkanSemaphore;

    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &backendSwapChain->vulkanSwapChain;
    presentInfo.pImageIndices = &backendFramebuffer->currentImageIndex;

    VkResult result = vkQueuePresentKHR(vulkanQueue, &presentInfo);

    switch (result) {
        case VK_ERROR_OUT_OF_DATE_KHR:
            return PresentationErrors::OutOfDate;
        case VK_SUBOPTIMAL_KHR:
            return PresentationErrors::Suboptimal;
        case VK_SUCCESS:
            return PresentationErrors::None;
        default:
            GFXTK_LOG_F("failed to present swap chain frame!");
    }
}
