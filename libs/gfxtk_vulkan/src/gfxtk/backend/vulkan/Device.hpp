#ifndef GFXTK_BACKEND_VULKAN_DEVICE_HPP
#define GFXTK_BACKEND_VULKAN_DEVICE_HPP

#include <gfxtk/InstanceDescriptor.hpp>
#include <gfxtk/DeviceInfo.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <vk_mem_alloc.h>
#include "SwapChainConfig.hpp"
#include "Instance.hpp"

namespace gfxtk::backend {
    struct Fence;

    struct Device {
        // --== Standard Backend GPU Functions ==--
        static std::vector<DeviceInfo> getDevices(
                std::unique_ptr<Instance> const& instance,
                backend::SwapChainConfig* swapChainConfig
        );
        static std::shared_ptr<Device> create(
                std::unique_ptr<Instance> const& instance,
                DeviceInfo const& deviceInfo,
                std::vector<QueueFamily> const& chosenQueues,
                backend::SwapChainConfig* swapChainConfig
        );
        void waitForFence(std::shared_ptr<backend::Fence> const& fence, uint64_t timeout);
        void waitForFences(std::vector<std::shared_ptr<backend::Fence>> const& fences, uint64_t timeout);
        void resetFence(std::shared_ptr<backend::Fence> const& fence);
        void resetFences(std::vector<std::shared_ptr<backend::Fence>> const& fences);
        void waitIdle();

        // --== Vulkan-specific Window Members ==--
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
        VmaAllocator allocator;

        Device(VkPhysicalDevice physicalDevice, VkDevice logicalDevice, VmaAllocator allocator)
                : physicalDevice(physicalDevice), logicalDevice(logicalDevice), allocator(allocator) {}
        ~Device();

    private:
        static std::vector<QueueFamily> getQueueFamiliesForPhysicalDevice(
                VkPhysicalDevice physicalDevice,
                VkSurfaceKHR surface
        );
        static VkPhysicalDevice getPhysicalDeviceByName(VkInstance instance, std::string const& name);
        static bool getDeviceIsSuitable(VkPhysicalDevice device, std::vector<char const*> const& requiredExtensions);

    };
}

#endif //GFXTK_BACKEND_VULKAN_DEVICE_HPP
