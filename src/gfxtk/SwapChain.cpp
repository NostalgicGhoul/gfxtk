#include "SwapChain.hpp"
#include "RenderPassAttachment.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/SwapChain.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/SwapChain.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::SwapChain gfxtk::SwapChain::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::vector<QueueFamily> const& chosenQueueFamilies,
        std::shared_ptr<backend::SwapChainConfig>& config
) {
    return gfxtk::SwapChain(
            backend::SwapChain::create(backendDevice, chosenQueueFamilies, config)
    );
}

gfxtk::SwapChain::SwapChain(std::shared_ptr<backend::SwapChain> backendSwapChain)
        : _backendSwapChain(std::move(backendSwapChain)) {}

gfxtk::SwapChain::~SwapChain() = default;

void gfxtk::SwapChain::configureFramebuffers(gfxtk::RenderPassAttachment const& renderPassAttachment) {
    _backendSwapChain->configureFramebuffers(renderPassAttachment._backendRenderPassAttachment);
}

gfxtk::Framebuffer gfxtk::SwapChain::getFramebuffer(
        uint32_t frameIndex,
        gfxtk::Semaphore& frameAvailableSemaphore,
        gfxtk::Fence& inFlightFence
) {
    FramebufferErrors outFramebufferErrors = FramebufferErrors::None;
    return gfxtk::Framebuffer(
            _backendSwapChain->getFramebuffer(
                    frameIndex,
                    frameAvailableSemaphore._backendSemaphore,
                    inFlightFence._backendFence,
                    &outFramebufferErrors
            ),
            outFramebufferErrors
    );
}

uint32_t gfxtk::SwapChain::framesInFlight() const {
    return _backendSwapChain->framesInFlight();
}

uint32_t gfxtk::SwapChain::nextFrameIndex() {
    return _backendSwapChain->nextFrameIndex();
}
