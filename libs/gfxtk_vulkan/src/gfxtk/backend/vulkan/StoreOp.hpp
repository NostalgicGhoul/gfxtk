#ifndef GFXTK_BACKEND_VULKAN_STOREOP_HPP
#define GFXTK_BACKEND_VULKAN_STOREOP_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/StoreOp.hpp>

namespace gfxtk::backend {
    struct StoreOp {
        static VkAttachmentStoreOp convert(gfxtk::StoreOp storeOp);

    };
}

#endif //GFXTK_BACKEND_VULKAN_STOREOP_HPP
