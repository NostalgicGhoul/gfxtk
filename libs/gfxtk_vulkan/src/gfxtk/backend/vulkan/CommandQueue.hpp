#ifndef GFXTK_BACKEND_VULKAN_COMMANDQUEUE_HPP
#define GFXTK_BACKEND_VULKAN_COMMANDQUEUE_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/QueueFamily.hpp>
#include <gfxtk/PipelineStage.hpp>
#include <gfxtk/PresentationErrors.hpp>
#include "Device.hpp"
#include "CommandBuffer.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "SwapChain.hpp"

namespace gfxtk::backend {
    struct CommandQueue {
        static std::shared_ptr<CommandQueue> createRenderCommandQueue(
                std::shared_ptr<backend::Device> const& backendDevice,
                size_t numberCommandBuffers,
                QueueFamily const& graphicsQueue
        );
        std::unique_ptr<CommandBuffer> getCommandBuffer(size_t commandBufferIndex);
        void submit(
                std::unique_ptr<backend::CommandBuffer> const& backendCommandBuffer,
                std::shared_ptr<backend::Fence> const& backendFence
        );
        void submit(
                std::shared_ptr<backend::Semaphore> const& waitBackendSemaphore,
                gfxtk::PipelineStage waitPipelineStage,
                std::unique_ptr<backend::CommandBuffer> const& backendCommandBuffer,
                std::shared_ptr<backend::Semaphore> const& signalBackendSemaphore,
                std::shared_ptr<backend::Fence> const& backendFence
        );
        PresentationErrors present(
                std::shared_ptr<backend::Semaphore> const& waitBackendSemaphore,
                std::shared_ptr<backend::SwapChain> const& backendSwapChain,
                std::unique_ptr<backend::Framebuffer> const& backendFramebuffer
        );

        VkDevice vulkanDevice;
        VkQueue vulkanQueue;
        VkCommandPool vulkanCommandPool;
        std::vector<VkCommandBuffer> vulkanCommandBuffers;

        CommandQueue(
                VkDevice vulkanDevice,
                VkQueue vulkanQueue,
                VkCommandPool vulkanCommandPool,
                std::vector<VkCommandBuffer> vulkanCommandBuffers
        ) : vulkanDevice(vulkanDevice),
            vulkanQueue(vulkanQueue),
            vulkanCommandPool(vulkanCommandPool),
            vulkanCommandBuffers(std::move(vulkanCommandBuffers)) {}
        ~CommandQueue() {
            vkDestroyCommandPool(vulkanDevice, vulkanCommandPool, nullptr);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_COMMANDQUEUE_HPP
