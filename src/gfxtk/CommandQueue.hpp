#ifndef GFXTK_COMMANDQUEUE_HPP
#define GFXTK_COMMANDQUEUE_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/QueueFamily.hpp>
#include <gfxtk/PipelineStage.hpp>
#include <gfxtk/PresentationErrors.hpp>
#include "SwapChain.hpp"
#include "CommandBuffer.hpp"

namespace gfxtk {
    namespace backend {
        struct Device;
        struct CommandQueue;
    }

    class GFXTK_EXPORT CommandQueue {
    public:
        static CommandQueue createRenderCommandQueue(
                std::shared_ptr<backend::Device> const& backendDevice,
                SwapChain const& swapChain,
                QueueFamily const& graphicsQueueFamily
        );

        CommandQueue() : _backendCommandQueue(nullptr) {}
        ~CommandQueue();

        [[nodiscard]]
        bool isValid() const { return _backendCommandQueue != nullptr; }

        CommandBuffer getCommandBufferForFrame(Framebuffer const& currentFramebuffer);

        void submit(
                Semaphore& waitSemaphore,
                PipelineStage waitPipelineStage,
                CommandBuffer& commandBuffer,
                Semaphore& signalSemaphore,
                std::optional<Fence> fence = std::nullopt
        );
        PresentationErrors present(
                Semaphore& waitSemaphore,
                SwapChain const& swapChain,
                Framebuffer const& framebuffer
        );

    private:
        std::shared_ptr<backend::CommandQueue> _backendCommandQueue;

        explicit CommandQueue(std::shared_ptr<backend::CommandQueue> backendCommandQueue);

    };
}

#endif //GFXTK_COMMANDQUEUE_HPP
