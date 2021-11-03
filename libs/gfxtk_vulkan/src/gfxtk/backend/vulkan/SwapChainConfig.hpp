#ifndef GFXTK_BACKEND_VULKAN_SWAPCHAINCONFIG_HPP
#define GFXTK_BACKEND_VULKAN_SWAPCHAINCONFIG_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/PixelFormat.hpp>
#include <gfxtk/ColorSpace.hpp>
#include <gfxtk/Extent2D.hpp>

namespace gfxtk::backend {
    struct Instance;
    struct Window;

    struct Surface {
        VkInstance cachedVulkanInstance;
        VkSurfaceKHR surface;

        Surface(VkInstance cachedVulkanInstance, VkSurfaceKHR surface)
                : cachedVulkanInstance(cachedVulkanInstance), surface(surface) {}
        ~Surface();

        static std::shared_ptr<Surface> create(VkInstance cachedVulkanInstance, VkSurfaceKHR surface) {
            return std::make_shared<Surface>(cachedVulkanInstance, surface);
        }

    };

    struct SwapChainConfig {
        // Surface will be stored in a created `SwapChain` as well. I keep a shared_ptr for it because C++ doesn't have
        // any concept of lifetimes for me to be able to say "surface is 'dead' after the swap chain is created" to
        // prevent issues from potentially accessing `SwapChainConfig::surface` after creating the swap chain. This
        // solves that issue in an ugly way.
        std::shared_ptr<Surface> surface;
        VkFormat pixelFormat;
        VkColorSpaceKHR colorSpace;
        VkExtent2D extent;
        uint32_t framesInFlight;
        // NOTE: Presentation mode is currently defaulted to FIFO. I don't see alternatives in Metal or DX12, so I'm
        //       forcing this decision. You may be able to configure this in the future but for now my 2 seconds of
        //       effort into research has led me to just choose to `FIFO` due to it being the only required presentation
        //       mode and allowing double buffering.

        SwapChainConfig(
                VkInstance cachedVulkanInstance,
                VkSurfaceKHR surface,
                VkFormat pixelFormat,
                VkColorSpaceKHR colorSpace,
                VkExtent2D extent,
                uint32_t framesInFlight
        ) : surface(Surface::create(cachedVulkanInstance, surface)),
            pixelFormat(pixelFormat),
            colorSpace(colorSpace),
            extent(extent),
            framesInFlight(framesInFlight) {}

        static std::shared_ptr<SwapChainConfig> create(
                std::unique_ptr<Instance> const& instance,
                std::shared_ptr<backend::Window> const& window,
                PixelFormat pixelFormat,
                ColorSpace colorSpace,
                uint32_t framesInFlight
        );

        void updateExtent(gfxtk::Extent2D newExtent) {
            extent.width = newExtent.width;
            extent.height = newExtent.height;
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_SWAPCHAINCONFIG_HPP
