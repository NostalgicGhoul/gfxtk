#ifndef GFXTK_BACKEND_VULKAN_INDEXTYPE_HPP
#define GFXTK_BACKEND_VULKAN_INDEXTYPE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/IndexType.hpp>

namespace gfxtk::backend {
    struct IndexType {
        static VkIndexType convert(gfxtk::IndexType indexType);

    };
}

#endif //GFXTK_BACKEND_VULKAN_INDEXTYPE_HPP
