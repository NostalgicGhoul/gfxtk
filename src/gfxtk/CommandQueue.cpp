#include "CommandQueue.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/CommandQueue.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/CommandQueue.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::CommandQueue gfxtk::CommandQueue::createRenderCommandQueue(
        std::shared_ptr<backend::Device> const& backendDevice,
        size_t numberCommandBuffers,
        QueueFamily const& graphicsQueueFamily
) {
    return gfxtk::CommandQueue(
            backend::CommandQueue::createRenderCommandQueue(
                    backendDevice,
                    numberCommandBuffers,
                    graphicsQueueFamily
            )
    );
}

gfxtk::CommandQueue::CommandQueue(std::shared_ptr<backend::CommandQueue> backendCommandQueue)
        : _backendCommandQueue(std::move(backendCommandQueue)) {}

gfxtk::CommandQueue::~CommandQueue() = default;

gfxtk::CommandBuffer gfxtk::CommandQueue::getCommandBuffer(size_t commandBufferIndex) {
    return gfxtk::CommandBuffer(_backendCommandQueue->getCommandBuffer(commandBufferIndex));
}

void gfxtk::CommandQueue::submit(
        gfxtk::CommandBuffer& commandBuffer,
        std::optional<Fence> fence
) {
    if (fence.has_value()) {
        _backendCommandQueue->submit(
                commandBuffer._backendCommandBuffer,
                fence.value()._backendFence
        );
    } else {
        _backendCommandQueue->submit(
                commandBuffer._backendCommandBuffer,
                nullptr
        );
    }
}

void gfxtk::CommandQueue::submit(
        gfxtk::Semaphore& waitSemaphore,
        gfxtk::PipelineStage waitPipelineStage,
        gfxtk::CommandBuffer& commandBuffer,
        gfxtk::Semaphore& signalSemaphore,
        std::optional<gfxtk::Fence> fence
) {
    if (fence.has_value()) {
        _backendCommandQueue->submit(
                waitSemaphore._backendSemaphore,
                waitPipelineStage,
                commandBuffer._backendCommandBuffer,
                signalSemaphore._backendSemaphore,
                fence.value()._backendFence
        );
    } else {
        _backendCommandQueue->submit(
                waitSemaphore._backendSemaphore,
                waitPipelineStage,
                commandBuffer._backendCommandBuffer,
                signalSemaphore._backendSemaphore,
                nullptr
        );
    }
}

gfxtk::PresentationErrors gfxtk::CommandQueue::present(
        gfxtk::Semaphore& waitSemaphore,
        gfxtk::SwapChain const& swapChain,
        gfxtk::Framebuffer const& framebuffer
) {
    return _backendCommandQueue->present(
            waitSemaphore._backendSemaphore,
            swapChain._backendSwapChain,
            framebuffer._backendFramebuffer
    );
}
