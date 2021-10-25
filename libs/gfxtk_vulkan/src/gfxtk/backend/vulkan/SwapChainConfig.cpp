#include "SwapChainConfig.hpp"
#include "PixelFormat.hpp"
#include "ColorSpace.hpp"
#include "Instance.hpp"
#include <gfxtk/log.hpp>

#ifdef GFXTK_WINDOW_BACKEND_GLFW
#include <gfxtk/backend/glfw/Window.hpp>
#else
#error unknown/unsupported windowing API backend!
#endif

gfxtk::backend::Surface::~Surface() {
    vkDestroySurfaceKHR(cachedVulkanInstance, surface, nullptr);
}

std::shared_ptr<gfxtk::backend::SwapChainConfig> gfxtk::backend::SwapChainConfig::create(
        std::unique_ptr<Instance> const& instance,
        std::shared_ptr<backend::Window> const& window,
        gfxtk::PixelFormat pixelFormat,
        gfxtk::ColorSpace colorSpace,
        uint32_t framesInFlight
) {
    VkFormat vulkanPixelFormat = backend::PixelFormat::convertToVkFormat(pixelFormat);
    VkColorSpaceKHR vulkanColorSpace = backend::ColorSpace::convertToVkColorSpaceKHR(colorSpace);

#ifdef GFXTK_WINDOW_BACKEND_GLFW
    VkSurfaceKHR resultSurface;

    if (glfwCreateWindowSurface(instance->vulkanInstance, window->window, nullptr, &resultSurface) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create a Vulkan surface using the GLFW window backend!");
    }

    VkExtent2D extent2D{};
    extent2D.width = window->getWidth();
    extent2D.height = window->getHeight();

    return std::make_shared<SwapChainConfig>(
            instance->vulkanInstance,
            resultSurface,
            vulkanPixelFormat,
            vulkanColorSpace,
            extent2D,
            framesInFlight
    );
#else
#error gfxtk::backend::SwapChainConfig::create has not been implemented for this windowing API backend yet!
#endif
}
