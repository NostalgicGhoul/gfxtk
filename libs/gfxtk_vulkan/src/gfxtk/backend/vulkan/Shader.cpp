#include "Shader.hpp"
#include "ShaderLibrary.hpp"
#include <gfxtk/log.hpp>

std::shared_ptr<gfxtk::backend::Shader> gfxtk::backend::Shader::create(
        std::unique_ptr<backend::ShaderLibrary> const& shaderLibrary,
        std::string const& name,
        std::vector<char> const& spirV
) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = spirV.size();
    createInfo.pCode = reinterpret_cast<uint32_t const*>(spirV.data());

    VkShaderModule shaderModule;

    if (vkCreateShaderModule(shaderLibrary->vulkanDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to properly create `gfxtk::Shader` using `Vulkan` backend!");
    }

    return std::make_shared<Shader>(shaderLibrary->vulkanDevice, shaderModule);
}

gfxtk::backend::Shader::~Shader() {
    vkDestroyShaderModule(vulkanDevice, vulkanShader, nullptr);
}
