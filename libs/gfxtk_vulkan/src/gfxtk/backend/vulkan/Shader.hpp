#ifndef GFXTK_BACKEND_VULKAN_SHADER_HPP
#define GFXTK_BACKEND_VULKAN_SHADER_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include "Device.hpp"

namespace gfxtk::backend {
    struct Shader {
        static std::shared_ptr<Shader> createFromSource(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::string const& sourceFilePath
        );

        VkDevice vulkanDevice;
        VkShaderModule vulkanShader;

        Shader(VkDevice vulkanDevice, VkShaderModule vulkanShader)
                : vulkanDevice(vulkanDevice), vulkanShader(vulkanShader) {}
        ~Shader();

    };
}

#endif //GFXTK_BACKEND_VULKAN_SHADER_HPP
