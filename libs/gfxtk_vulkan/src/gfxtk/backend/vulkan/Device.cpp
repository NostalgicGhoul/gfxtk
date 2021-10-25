#include "Device.hpp"
#include <gfxtk/log.hpp>
#include <vector>
#include <set>
#include "Fence.hpp"

std::vector<gfxtk::DeviceInfo> gfxtk::backend::Device::getDevices(
        std::unique_ptr<Instance> const& instance,
        gfxtk::backend::SwapChainConfig* swapChainConfig
) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance->vulkanInstance, &deviceCount, nullptr);

    std::vector<gfxtk::DeviceInfo> allDevices;
    allDevices.reserve(deviceCount);

    if (deviceCount != 0) {
        std::vector<VkPhysicalDevice> vkDevices(deviceCount);
        vkEnumeratePhysicalDevices(instance->vulkanInstance, &deviceCount, vkDevices.data());

        for (auto const& device : vkDevices) {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(device, &deviceProperties);

            DeviceType deviceType;

            switch (deviceProperties.deviceType) {
                case VK_PHYSICAL_DEVICE_TYPE_CPU:
                    deviceType = DeviceType::CPU;
                    break;
                case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                    deviceType = DeviceType::IntegratedGPU;
                    break;
                case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
                    deviceType = DeviceType::VirtualGPU;
                    break;
                case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                    deviceType = DeviceType::DiscreteGPU;
                    break;
                default:
                    deviceType = DeviceType::Unknown;
                    break;
            }

            allDevices.emplace_back(
                    DeviceInfo(
                            deviceType,
                            deviceProperties.deviceName,
                            getQueueFamiliesForPhysicalDevice(device, swapChainConfig->surface->surface)
                    )
            );
        }
    }

    return allDevices;
}

std::shared_ptr<gfxtk::backend::Device> gfxtk::backend::Device::create(
        std::unique_ptr<Instance> const& instance,
        gfxtk::DeviceInfo const& deviceInfo,
        std::vector<QueueFamily> const& chosenQueues,
        backend::SwapChainConfig* swapChainConfig
) {
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    queueCreateInfos.reserve(chosenQueues.size());

    float queuePriority = 1.0f;
    for (auto const& chosenQueue : chosenQueues) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = chosenQueue.id();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    // TODO: We need to fill this based on the `InitConfig` requirements
    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    std::vector<char const*> requiredExtensions;

    //VK_KHR_surface, VK_EXT_metal_surface, VK_EXT_debug_utils, VK_KHR_swapchain
    if (swapChainConfig != nullptr) {
        requiredExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    if (instance->cachedInitConfig.debugMode) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(instance->vulkanValidationLayers.size());
        createInfo.ppEnabledLayerNames = instance->vulkanValidationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    VkPhysicalDevice physicalDevice = getPhysicalDeviceByName(instance->vulkanInstance, deviceInfo.name());
    VkDevice logicalDevice = VK_NULL_HANDLE;

    if (!getDeviceIsSuitable(physicalDevice, requiredExtensions)) {
        GFXTK_LOG_F("chosen device does not support all required `Vulkan` extensions!");
    }

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create device using `Vulkan` backend!");
    }

    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.vulkanApiVersion = instance->vulkanVersion;
    allocatorInfo.physicalDevice = physicalDevice;
    allocatorInfo.device = logicalDevice;
    allocatorInfo.instance = instance->vulkanInstance;

    VmaAllocator allocator;
    vmaCreateAllocator(&allocatorInfo, &allocator);

    return std::make_shared<gfxtk::backend::Device>(physicalDevice, logicalDevice, allocator);
}

std::vector<gfxtk::QueueFamily> gfxtk::backend::Device::getQueueFamiliesForPhysicalDevice(
        VkPhysicalDevice physicalDevice,
        VkSurfaceKHR surface
) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<QueueFamily> result;

    if (queueFamilyCount > 0) {
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        result.reserve(queueFamilyCount);

        size_t i = 0;
        for (auto const& queueFamily : queueFamilies) {
            QueueFlags resultFlags = QueueFlags::None;

            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                resultFlags |= QueueFlags::Render;
            }

            if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                resultFlags |= QueueFlags::Compute;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

            if (presentSupport) {
                resultFlags |= QueueFlags::Present;
            }

            result.emplace_back(QueueFamily(i, resultFlags));
            ++i;
        }
    }

    return result;
}

VkPhysicalDevice gfxtk::backend::Device::getPhysicalDeviceByName(VkInstance instance, std::string const& name) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> vkDevices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, vkDevices.data());

    for (auto const& device : vkDevices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        if (deviceProperties.deviceName == name) {
            return device;
        }
    }

    GFXTK_LOG_F("GPU `" + name + "` was not found or was not compatible with `Vulkan`!");
    return nullptr;
}

gfxtk::backend::Device::~Device() {
    vmaDestroyAllocator(allocator);
    vkDestroyDevice(logicalDevice, nullptr);
}

bool gfxtk::backend::Device::getDeviceIsSuitable(
        VkPhysicalDevice device,
        std::vector<char const*> const& requiredExtensions
) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensionStrings(requiredExtensions.begin(), requiredExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensionStrings.erase(extension.extensionName);
    }

    // NOTE: Yes. I should be checking swap chain support here if I _really_ wanted to be proper about this. But, I
    //       don't have the energy to deal with the amount of cross-contamination that would cause to support that. I
    //       fully disagree with the idea that the swap chain should be a tie between the 1. window manager, 2. graphics
    //       API, and 3. the _device itself_. Sure, perhaps you get a slight performance boost by tying the swap chain
    //       support to the _hardware_ but that dirties the API WAY too much for my liking. And if you do that _I should
    //       be able to query for swap chain support without needing to know about the window I'm rendering to_. I hate
    //       it. And so my solution to this anger is to just assume that the device supports swap chains. Because lets
    //       be honest here: _everyone_ is going to have a GPU supporting swap chains properly if they support Vulkan
    //       and there is no _real_ point in checking for support.
    //       Again, I fully believe the swap chain should be a _CPU side_ abstraction that is built _only in the window
    //       manager_ with no need to check the actual device in use. Sure, this would probably have a speed penalty
    //       but that penalty would be so negligible compared to the purity of the API. All the window manager would
    //       need is to have a generic, device and API agnostic way to allocate memory and manipulate that memory. With
    //       that you could fully and completely implement swap chain support _without tying the window manager to
    //       Vulkan, DX12, or Metal_, _without forcing the Vulkan API to know about the window manager_, etc. All
    //       Vulkan would have to do is accept the generically allocated block of memory from the Window manager as a
    //       texture. /rant

    return requiredExtensionStrings.empty();
}

void gfxtk::backend::Device::waitForFence(std::shared_ptr<backend::Fence> const& fence, uint64_t timeout) {
    vkWaitForFences(logicalDevice, 1, &fence->vulkanFence, VK_TRUE, timeout);
}

void gfxtk::backend::Device::waitForFences(
        std::vector<std::shared_ptr<backend::Fence>> const& fences,
        uint64_t timeout
) {
    std::vector<VkFence> vulkanFences;
    vulkanFences.reserve(fences.size());

    for (auto const& fence : fences) {
        vulkanFences.push_back(fence->vulkanFence);
    }

    vkWaitForFences(logicalDevice, vulkanFences.size(), vulkanFences.data(), VK_TRUE, timeout);
}

void gfxtk::backend::Device::resetFence(std::shared_ptr<backend::Fence> const& fence) {
    vkResetFences(logicalDevice, 1, &fence->vulkanFence);
}

void gfxtk::backend::Device::resetFences(std::vector<std::shared_ptr<backend::Fence>> const& fences) {
    std::vector<VkFence> vulkanFences;
    vulkanFences.reserve(fences.size());

    for (auto const& fence : fences) {
        vulkanFences.push_back(fence->vulkanFence);
    }

    vkResetFences(logicalDevice, vulkanFences.size(), vulkanFences.data());
}

void gfxtk::backend::Device::waitIdle() {
    vkDeviceWaitIdle(logicalDevice);
}
