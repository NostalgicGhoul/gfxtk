#include "Instance.hpp"
#include <gfxtk/log.hpp>
#include <cstring>

#ifdef GFXTK_WINDOW_BACKEND_GLFW
#include <gfxtk/backend/glfw/Window.hpp>
#endif

VkResult gfxtk_backend_vulkan_createDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerCreateInfoEXT const* pCreateInfo,
        VkAllocationCallbacks const* pAllocator,
        VkDebugUtilsMessengerEXT* pDebugMessenger
) {
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT")
    );

    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void gfxtk_backend_vulkan_destroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        VkAllocationCallbacks const* pAllocator
) {
    auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT")
    );

    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL gfxtk_backend_vulkan_debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData,
        void* pUserData
) {
    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            gfxtk::log::w(
                    "Backend Validation Layer",
                    "Vulkan",
                    pCallbackData->messageIdNumber,
                    pCallbackData->pMessage
            );
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            gfxtk::log::e(
                    "Backend Validation Layer",
                    "Vulkan",
                    pCallbackData->messageIdNumber,
                    pCallbackData->pMessage
            );
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
#ifdef GFXTK_VERBOSE_LOGGING
            gfxtk::log::d(
                    "Backend Validation Layer",
                    "Vulkan",
                    pCallbackData->messageIdNumber,
                    pCallbackData->pMessage
            );
#endif
            break;
        default:
            gfxtk::log::i(
                    "Backend Validation Layer",
                    "Vulkan",
                    pCallbackData->messageIdNumber,
                    pCallbackData->pMessage
            );
            break;
    }

    return VK_FALSE;
}

std::unique_ptr<gfxtk::backend::Instance> gfxtk::backend::Instance::create(gfxtk::InstanceDescriptor const& initConfig) {
    std::vector<char const*> requiredExtensions;

#ifdef GFXTK_WINDOW_BACKEND_GLFW
    uint32_t glfwExtensionCount = 0;
    char const** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    requiredExtensions = std::vector<char const*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
#endif

    // Result variables
    VkInstance vulkanInstance;
    VkDebugUtilsMessengerEXT vulkanDebugUtilsMessengerEXT;
    std::vector<char const*> vulkanValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

    if (initConfig.debugMode) {
        checkValidationLayerSupport(vulkanValidationLayers);
        requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = initConfig.applicationName.c_str();
    appInfo.applicationVersion =
            VK_MAKE_VERSION(
                    initConfig.applicationVersion.major(),
                    initConfig.applicationVersion.minor(),
                    initConfig.applicationVersion.patch()
            );
    appInfo.pEngineName = initConfig.engineName.c_str();
    appInfo.engineVersion =
            VK_MAKE_VERSION(
                    initConfig.engineVersion.major(),
                    initConfig.engineVersion.minor(),
                    initConfig.engineVersion.patch()
            );
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

    if (initConfig.debugMode) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(vulkanValidationLayers.size());
        createInfo.ppEnabledLayerNames = vulkanValidationLayers.data();

        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = gfxtk_backend_vulkan_debugCallback;
        createInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
    } else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &vulkanInstance) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create a Vulkan instance!");
    }

    if (initConfig.debugMode) {
        if (gfxtk_backend_vulkan_createDebugUtilsMessengerEXT(
                vulkanInstance, &debugCreateInfo, nullptr, &vulkanDebugUtilsMessengerEXT) != VK_SUCCESS) {
            GFXTK_LOG_F("failed to set up debug messenger for Vulkan backend!");
        }
    }

    return std::make_unique<Instance>(
            initConfig,
            vulkanInstance,
            appInfo.apiVersion,
            vulkanDebugUtilsMessengerEXT,
            vulkanValidationLayers
    );
}

void gfxtk::backend::Instance::checkValidationLayerSupport(std::vector<char const*> const& vulkanValidationLayers) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (auto layerName : vulkanValidationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            GFXTK_LOG_F("required Vulkan validation layer `" + std::string(layerName) + "` is not available on this GPU...");
        }
    }
}

gfxtk::backend::Instance::Instance(
        gfxtk::InstanceDescriptor cachedInitConfig,
        VkInstance vulkanInstance,
        uint32_t vulkanVersion,
        VkDebugUtilsMessengerEXT vulkanDebugUtilsMessengerEXT,
        std::vector<const char *> vulkanValidationLayers
) : cachedInitConfig(std::move(cachedInitConfig)),
    vulkanInstance(vulkanInstance),
    vulkanVersion(vulkanVersion),
    vulkanDebugUtilsMessengerEXT(vulkanDebugUtilsMessengerEXT),
    vulkanValidationLayers(std::move(vulkanValidationLayers)) {}

gfxtk::backend::Instance::~Instance() {
    if (vulkanDebugUtilsMessengerEXT != VK_NULL_HANDLE) {
        gfxtk_backend_vulkan_destroyDebugUtilsMessengerEXT(vulkanInstance, vulkanDebugUtilsMessengerEXT, nullptr);
    }

    vkDestroyInstance(vulkanInstance, nullptr);
}
