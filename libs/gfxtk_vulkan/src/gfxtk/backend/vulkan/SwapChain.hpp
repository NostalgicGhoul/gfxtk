#ifndef GFXTK_BACKEND_VULKAN_SWAPCHAIN_HPP
#define GFXTK_BACKEND_VULKAN_SWAPCHAIN_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/FramebufferErrors.hpp>
#include "SwapChainConfig.hpp"
#include "Device.hpp"
#include "RenderPassAttachment.hpp"
#include "Framebuffer.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"

namespace gfxtk::backend {
    struct SwapChain {
        static std::shared_ptr<SwapChain> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::vector<QueueFamily> const& chosenQueueFamilies,
                std::shared_ptr<backend::SwapChainConfig>& config
        );

        std::unique_ptr<backend::Framebuffer> getFramebuffer(
                uint32_t index,
                std::shared_ptr<backend::Semaphore> const& backendSemaphore,
                std::shared_ptr<backend::Fence> const& backendFence,
                gfxtk::FramebufferErrors* outFramebufferErrors
        );
        [[nodiscard]]
        uint32_t framesInFlight() const { return _framesInFlight; }
        [[nodiscard]]
        uint32_t nextFrameIndex();

        // Required for destruction
        VkDevice vulkanDevice;
        std::shared_ptr<Surface> surface;
        VkSwapchainKHR vulkanSwapChain;
        VkExtent2D vulkanSwapChainExtent;
        VkFormat vulkanSwapChainImagePixelFormat;
        std::vector<VkImage> vulkanSwapChainImages;
        std::vector<VkImageView> vulkanSwapChainImageViews;
        std::vector<VkFramebuffer> vulkanSwapChainFramebuffers;
        uint32_t currentFramebufferIndex;
        uint32_t _framesInFlight;
        // NOTE: These are NOT owned by us, so we do not destroy them, these are given to us by the main thread only.
        std::vector<VkFence> imagesInFlightFences;

        SwapChain(
                VkDevice vulkanDevice,
                std::shared_ptr<Surface> surface,
                VkSwapchainKHR vulkanSwapChain,
                VkExtent2D vulkanSwapChainExtent,
                VkFormat vulkanSwapChainImagePixelFormat,
                std::vector<VkImage> vulkanSwapChainImages,
                std::vector<VkImageView> vulkanSwapChainImageViews,
                uint32_t framesInFlight
        ) : vulkanDevice(vulkanDevice),
            surface(std::move(surface)),
            vulkanSwapChain(vulkanSwapChain),
            vulkanSwapChainExtent(vulkanSwapChainExtent),
            vulkanSwapChainImagePixelFormat(vulkanSwapChainImagePixelFormat),
            vulkanSwapChainImages(std::move(vulkanSwapChainImages)),
            vulkanSwapChainImageViews(std::move(vulkanSwapChainImageViews)),
            currentFramebufferIndex(0),
            _framesInFlight(framesInFlight) {
            imagesInFlightFences.resize(this->vulkanSwapChainImages.size());
        }
        ~SwapChain();

        void configureFramebuffers(std::shared_ptr<backend::RenderPassAttachment> const& renderPassAttachment);
        void cleanupFramebuffers();

    };
}

#endif //GFXTK_BACKEND_VULKAN_SWAPCHAIN_HPP
