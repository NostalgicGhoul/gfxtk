#ifndef GFXTK_BACKEND_VULKAN_SHADERSTAGEFLAGS_HPP
#define GFXTK_BACKEND_VULKAN_SHADERSTAGEFLAGS_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/ShaderStageFlags.hpp>

namespace gfxtk::backend {
    class ShaderStageFlags {
    public:
        static VkShaderStageFlags convertToVkShaderStageFlags(gfxtk::ShaderStageFlags shaderStageFlags);

    };
}

#endif //GFXTK_BACKEND_VULKAN_SHADERSTAGEFLAGS_HPP
