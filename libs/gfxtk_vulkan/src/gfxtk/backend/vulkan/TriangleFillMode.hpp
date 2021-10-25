#ifndef GFXTK_BACKEND_VULKAN_TRIANGLEFILLMODE_HPP
#define GFXTK_BACKEND_VULKAN_TRIANGLEFILLMODE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/TriangleFillMode.hpp>

namespace gfxtk::backend {
    struct TriangleFillMode {
        static VkPolygonMode convert(gfxtk::TriangleFillMode fillMode);

    };
}

#endif //GFXTK_BACKEND_VULKAN_TRIANGLEFILLMODE_HPP
