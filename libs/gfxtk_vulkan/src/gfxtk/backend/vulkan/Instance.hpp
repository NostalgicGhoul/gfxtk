#ifndef GFXTK_BACKEND_VULKAN_INSTANCE_HPP
#define GFXTK_BACKEND_VULKAN_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <gfxtk/InstanceDescriptor.hpp>

namespace gfxtk::backend {
    struct Instance {
        InstanceDescriptor cachedInitConfig;
        VkInstance vulkanInstance;
        uint32_t vulkanVersion;
        VkDebugUtilsMessengerEXT vulkanDebugUtilsMessengerEXT;
        std::vector<char const*> vulkanValidationLayers;

        Instance(
                InstanceDescriptor cachedInitConfig,
                VkInstance vulkanInstance,
                uint32_t vulkanVersion,
                VkDebugUtilsMessengerEXT vulkanDebugUtilsMessengerEXT,
                std::vector<char const*> vulkanValidationLayers
        );
        ~Instance();

        static std::unique_ptr<Instance> create(InstanceDescriptor const& initConfig);

    private:
        static void checkValidationLayerSupport(std::vector<char const*> const& vulkanValidationLayers);

    };
}

#endif //GFXTK_BACKEND_VULKAN_INSTANCE_HPP
