#include "SwapChain.hpp"
#include "Device.hpp"
#include <gfxtk/log.hpp>

VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        VkPhysicalDevice device,
        VkSurfaceKHR surface,
        VkFormat requestedFormat,
        VkColorSpaceKHR requestedColorSpace
) {
    std::vector<VkSurfaceFormatKHR> availableFormats;

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        availableFormats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, availableFormats.data());
    }

    for (auto const& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
                availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    GFXTK_LOG_F("requested format and colorspace combination were not found for the provided swapchain!");
    // This will never be reached.
    return availableFormats[0];
}

std::shared_ptr<gfxtk::backend::SwapChain> gfxtk::backend::SwapChain::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::vector<QueueFamily> const& chosenQueueFamilies,
        std::shared_ptr<backend::SwapChainConfig>& config
) {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(backendDevice->physicalDevice, config->surface->surface, &capabilities);

    VkSurfaceFormatKHR surfaceFormat =
            chooseSwapSurfaceFormat(
                    backendDevice->physicalDevice,
                    config->surface->surface,
                    config->pixelFormat,
                    config->colorSpace
            );

    // TODO: Figure out why `imageCount` has to be `framesInFlight` on mac. It should be perfectly valid to have 3 GPU
    //       images but only 2 framebuffers for those images. Yet on mac this causes an issue with the 3rd image not
    //       being in the correct layout.
//    uint32_t imageCount = capabilities.minImageCount + 1;
    uint32_t imageCount = std::max(config->framesInFlight, capabilities.minImageCount);

    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
        imageCount = capabilities.maxImageCount;
    }

    config->framesInFlight = imageCount;

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = config->surface->surface;

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = config->extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    if (chosenQueueFamilies.size() > 1) {
        std::vector<uint32_t> queueFamilyIndices;
        queueFamilyIndices.reserve(chosenQueueFamilies.size());

        for (auto const& chosenQueueFamily: chosenQueueFamilies) {
            queueFamilyIndices.push_back(chosenQueueFamily.id());
        }

        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = queueFamilyIndices.size();
        createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapChain;

    if (vkCreateSwapchainKHR(backendDevice->logicalDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create swap chain on Vulkan backend!");
    }

    std::vector<VkImage> vulkanSwapChainImages;
    vkGetSwapchainImagesKHR(backendDevice->logicalDevice, swapChain, &imageCount, nullptr);
    vulkanSwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(backendDevice->logicalDevice, swapChain, &imageCount, vulkanSwapChainImages.data());

    std::vector<VkImageView> vulkanSwapChainImageViews;
    vulkanSwapChainImageViews.resize(vulkanSwapChainImages.size());

    for (size_t i = 0; i < vulkanSwapChainImages.size(); i++) {
        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image = vulkanSwapChainImages[i];
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = config->pixelFormat;
        imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
        imageViewCreateInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(backendDevice->logicalDevice, &imageViewCreateInfo, nullptr, &vulkanSwapChainImageViews[i]) != VK_SUCCESS) {
            GFXTK_LOG_F("failed to create image views on Vulkan backend!");
        }
    }

    return std::make_shared<SwapChain>(
            backendDevice->logicalDevice,
            config->surface,
            swapChain,
            config->extent,
            config->pixelFormat,
            vulkanSwapChainImages,
            vulkanSwapChainImageViews,
            config->framesInFlight
    );
}

gfxtk::backend::SwapChain::~SwapChain() {
    cleanupFramebuffers();

    for (auto imageView : vulkanSwapChainImageViews) {
        vkDestroyImageView(vulkanDevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(vulkanDevice, vulkanSwapChain, nullptr);
}

void gfxtk::backend::SwapChain::configureFramebuffers(
        std::shared_ptr<backend::RenderPassAttachment> const& renderPassAttachment
) {
    cleanupFramebuffers();

    if (renderPassAttachment != nullptr) {
        vulkanSwapChainFramebuffers.resize(vulkanSwapChainImageViews.size());

        for (size_t i = 0; i < vulkanSwapChainImageViews.size(); ++i) {
            VkImageView attachments[] = {
                    vulkanSwapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPassAttachment->vulkanRenderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = vulkanSwapChainExtent.width;
            framebufferInfo.height = vulkanSwapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(
                    vulkanDevice, &framebufferInfo, nullptr, &vulkanSwapChainFramebuffers[i]) != VK_SUCCESS) {
                GFXTK_LOG_F("failed to create framebuffer for Vulkan backend!");
            }
        }
    } else {
        vulkanSwapChainFramebuffers.resize(0);
    }
}

void gfxtk::backend::SwapChain::cleanupFramebuffers() {
    for (auto framebuffer : vulkanSwapChainFramebuffers) {
        vkDestroyFramebuffer(vulkanDevice, framebuffer, nullptr);
    }
}

std::unique_ptr<gfxtk::backend::Framebuffer> gfxtk::backend::SwapChain::getFramebuffer(
        uint32_t frameIndex,
        std::shared_ptr<backend::Semaphore> const& backendSemaphore,
        std::shared_ptr<backend::Fence> const& backendFence,
        gfxtk::FramebufferErrors* outFramebufferErrors
) {
    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(
            vulkanDevice,
            vulkanSwapChain,
            UINT64_MAX,
            backendSemaphore->vulkanSemaphore,
            VK_NULL_HANDLE,
            &imageIndex
    );

    switch (result) {
        case VK_ERROR_OUT_OF_DATE_KHR:
            *outFramebufferErrors = FramebufferErrors::OutOfDate;
            break;
        case VK_SUBOPTIMAL_KHR:
            *outFramebufferErrors = FramebufferErrors::Suboptimal;
            break;
        case VK_SUCCESS:
            *outFramebufferErrors = FramebufferErrors::None;
            break;
        default:
            GFXTK_LOG_F("failed to acquire next swap chain image on Vulkan backend!");
    }

    if (imagesInFlightFences[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(vulkanDevice, 1, &imagesInFlightFences[imageIndex], VK_TRUE, UINT64_MAX);
    }
    imagesInFlightFences[imageIndex] = backendFence->vulkanFence;

    VkFramebuffer vulkanFramebuffer = vulkanSwapChainFramebuffers[frameIndex];
    return std::make_unique<backend::Framebuffer>(vulkanFramebuffer, imageIndex);
}

uint32_t gfxtk::backend::SwapChain::nextFrameIndex() {
    auto result = currentFramebufferIndex;
    currentFramebufferIndex = (currentFramebufferIndex + 1) % _framesInFlight;
    return result;
}
