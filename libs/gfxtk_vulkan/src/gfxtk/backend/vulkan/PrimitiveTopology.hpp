#ifndef GFXTK_BACKEND_VULKAN_PRIMITIVETOPOLOGY_HPP
#define GFXTK_BACKEND_VULKAN_PRIMITIVETOPOLOGY_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/PrimitiveTopology.hpp>

namespace gfxtk::backend {
    struct PrimitiveTopology {
        static VkPrimitiveTopology convertToVkPrimitiveTopology(gfxtk::PrimitiveTopology primitiveTopology);

    };
}

#endif //GFXTK_BACKEND_VULKAN_PRIMITIVETOPOLOGY_HPP
