#ifndef GFXTK_SWAPCHAIN_HPP
#define GFXTK_SWAPCHAIN_HPP

#include <memory>
#include <vector>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/QueueFamily.hpp>
#include "Framebuffer.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"

namespace gfxtk {
    namespace backend {
        struct Device;
        struct SwapChain;
        struct SwapChainConfig;
    }

    class GFXTK_EXPORT RenderPassAttachment;

    class GFXTK_EXPORT SwapChain {
        friend class CommandQueue;

    public:
        static SwapChain create(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::vector<QueueFamily> const& chosenQueueFamilies,
                std::shared_ptr<backend::SwapChainConfig>& config
        );

        SwapChain() : _backendSwapChain(nullptr) {}
        ~SwapChain();

        [[nodiscard]]
        bool isValid() const { return _backendSwapChain != nullptr; }

        void configureFramebuffers(RenderPassAttachment const& renderPassAttachment);
        Framebuffer getFramebuffer(uint32_t index, Semaphore& frameAvailableSemaphore, Fence& inFlightFence);
        [[nodiscard]]
        uint32_t framesInFlight() const;
        [[nodiscard]]
        uint32_t nextFrameIndex();

    private:
        std::shared_ptr<backend::SwapChain> _backendSwapChain;

        explicit SwapChain(std::shared_ptr<backend::SwapChain> backendSwapChain);

    };
}

#endif //GFXTK_SWAPCHAIN_HPP
