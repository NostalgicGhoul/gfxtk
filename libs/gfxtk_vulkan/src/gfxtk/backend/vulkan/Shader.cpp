#include "Shader.hpp"
#include <fstream>
#include <gfxtk/log.hpp>

std::shared_ptr<gfxtk::backend::Shader> gfxtk::backend::Shader::createFromSource(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::string const& sourceFilePath
) {
    std::ifstream inputShaderStream(sourceFilePath + ".spv", std::ios::binary);

    if (!inputShaderStream.good()) {
        GFXTK_LOG_F("shader `" + sourceFilePath + "` was not found using Vulkan backend!");
    }

    auto spirV = std::vector<char>(std::istreambuf_iterator<char>(inputShaderStream), {});

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = spirV.size();
    createInfo.pCode = reinterpret_cast<uint32_t const*>(spirV.data());

    VkShaderModule shaderModule;

    if (vkCreateShaderModule(backendDevice->logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to properly create `gfxtk::Shader` using `Vulkan` backend!");
    }

    return std::make_shared<Shader>(backendDevice->logicalDevice, shaderModule);
}

gfxtk::backend::Shader::~Shader() {
    vkDestroyShaderModule(vulkanDevice, vulkanShader, nullptr);
}
