#ifndef GFXTK_SWAPCHAINCONFIG_HPP
#define GFXTK_SWAPCHAINCONFIG_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/PixelFormat.hpp>
#include <gfxtk/ColorSpace.hpp>
#include <gfxtk/Window.hpp>
#include <gfxtk/Extent2D.hpp>

namespace gfxtk {
    namespace backend {
        struct Instance;
        struct SwapChainConfig;
    }

    /**
     * `SwapChainConfig` is a class that only exists to try to make what I consider a _bad design_ in Vulkan, flow
     * better with Metal and DX12 backends.
     *
     * Vulkan requires a `VkSurfaceKHR` to exist _before you even start looking for a device_, `VkSwapchainKHR` also
     * requires a `VkDevice` to be created, and a `VkDevice` needs to know about the `VkSurfaceKHR` to be able to check
     * if any queues support presentation. This creates a horribly intertwined system where you have to force _all
     * layers of your code_ to know about the window manager (`VkSurfaceKHR` is only used when rendering to a window).
     * Vulkan is the ONLY API with this design. Metal does what I consider to be the _sane_ API design of forcing the
     * Window manager to implement all code needed for SwapChain support, allowing us to not need to know about the
     * window manager except for places _where we're explicitly asking it for the next frame's texture_. DX12, I hate
     * to admit, also does this MUCH more sane as it, too, allows you to create a `Device` _then_ `SwapChain` _with
     * only the window handle_.
     *
     * So the solution? DX12 has `DXGI_SWAP_CHAIN_DESC1`, Metal also has similar abilities to configure `CAMetalLayer`.
     * From this, I've decided to create this class as a "band-aid". It's ugly, shouldn't have to exist the way it does,
     * but here we are. The usage is ugly because of the fact that you will need a `Window` to create this and you will
     * have to pass it to `Device` during device creation. Neither of these things are required on _any other backend
     * API other than Vulkan_. I really don't want people to think I hate Vulkan. I don't. I'm actually a huge advocate
     * for open, cross-platform APIs and like Vulkan _way_ more than Metal and DX12. I'm just disappointed in the amount
     * of glue needed for swap chain support. Luckily it is set up in a way that it _should_ be possible to completely
     * replace Vulkan's swap chain support with something _better_ in the future.
     *
     * Usage:
     * ```
     * gfxtk::init(...);
     * auto window = gfxtk::Window::create(...);
     * auto swapChainConfig = gfxtk::SwapChainConfig::create(window, ...);
     * auto device = gfxtk::Device::createBestFit(flags, swapChainConfig);
     * auto swapChain = window->createSwapChain(swapChainConfig);
     * ```
     */
    class GFXTK_EXPORT SwapChainConfig {
        friend class Device;

    public:
        static SwapChainConfig create(
                std::unique_ptr<backend::Instance> const& instance,
                std::unique_ptr<Window> const& window,
                PixelFormat pixelFormat,
                ColorSpace colorSpace,
                uint32_t framesInFlight
        );

        void updateExtent(gfxtk::Extent2D newExtent);

        ~SwapChainConfig();

    private:
        std::shared_ptr<backend::SwapChainConfig> _backendSwapChainConfig;

        explicit SwapChainConfig(std::shared_ptr<backend::SwapChainConfig> backendSwapChainConfig);

    };
}

#endif //GFXTK_SWAPCHAINCONFIG_HPP
