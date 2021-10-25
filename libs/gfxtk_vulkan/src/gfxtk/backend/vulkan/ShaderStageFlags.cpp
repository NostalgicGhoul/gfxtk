#include "ShaderStageFlags.hpp"

VkShaderStageFlags gfxtk::backend::ShaderStageFlags::convertToVkShaderStageFlags(
        gfxtk::ShaderStageFlags shaderStageFlags
) {
    VkShaderStageFlags result = 0;

    if ((shaderStageFlags & gfxtk::ShaderStageFlags::Vertex) == gfxtk::ShaderStageFlags::Vertex) {
        result |= VK_SHADER_STAGE_VERTEX_BIT;
    }

    if ((shaderStageFlags & gfxtk::ShaderStageFlags::Fragment) == gfxtk::ShaderStageFlags::Fragment) {
        result |= VK_SHADER_STAGE_FRAGMENT_BIT;
    }

    if ((shaderStageFlags & gfxtk::ShaderStageFlags::Compute) == gfxtk::ShaderStageFlags::Compute) {
        result |= VK_SHADER_STAGE_COMPUTE_BIT;
    }

    return result;
}
