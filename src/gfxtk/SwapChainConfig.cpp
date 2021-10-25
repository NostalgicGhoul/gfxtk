#include "SwapChainConfig.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/SwapChainConfig.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::SwapChainConfig gfxtk::SwapChainConfig::create(
        std::unique_ptr<backend::Instance> const& instance,
        std::unique_ptr<Window> const& window,
        gfxtk::PixelFormat pixelFormat,
        gfxtk::ColorSpace colorSpace,
        uint32_t framesInFlight
) {
    return gfxtk::SwapChainConfig(
            backend::SwapChainConfig::create(
                    instance,
                    window->_backendWindow,
                    pixelFormat,
                    colorSpace,
                    framesInFlight
            )
    );
}

gfxtk::SwapChainConfig::SwapChainConfig(std::shared_ptr<backend::SwapChainConfig> backendSwapChainConfig)
        : _backendSwapChainConfig(std::move(backendSwapChainConfig)) {}

gfxtk::SwapChainConfig::~SwapChainConfig() = default;
