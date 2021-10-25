#ifndef GFXTK_BACKEND_VULKAN_SHADER_HPP
#define GFXTK_BACKEND_VULKAN_SHADER_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include "Device.hpp"

namespace gfxtk::backend {
    struct ShaderLibrary;

    struct Shader {
        static std::shared_ptr<Shader> create(
                std::unique_ptr<backend::ShaderLibrary> const& shaderLibrary,
                std::string const& name,
                std::vector<char> const& spirV
        );

        VkDevice vulkanDevice;
        VkShaderModule vulkanShader;

        Shader(VkDevice vulkanDevice, VkShaderModule vulkanShader)
                : vulkanDevice(vulkanDevice), vulkanShader(vulkanShader) {}
        ~Shader();

    };
}

#endif //GFXTK_BACKEND_VULKAN_SHADER_HPP
