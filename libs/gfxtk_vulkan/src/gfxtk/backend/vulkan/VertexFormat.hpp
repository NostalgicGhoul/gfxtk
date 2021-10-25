#ifndef GFXTK_BACKEND_VULKAN_VERTEXFORMAT_HPP
#define GFXTK_BACKEND_VULKAN_VERTEXFORMAT_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/VertexFormat.hpp>

namespace gfxtk::backend {
    struct VertexFormat {
        static VkFormat convertToVkFormat(gfxtk::VertexFormat vertexFormat);

    };
}

#endif //GFXTK_BACKEND_VULKAN_VERTEXFORMAT_HPP
