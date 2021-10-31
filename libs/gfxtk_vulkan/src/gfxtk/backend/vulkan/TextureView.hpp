#ifndef GFXTK_BACKEND_VULKAN_TEXTUREVIEW_HPP
#define GFXTK_BACKEND_VULKAN_TEXTUREVIEW_HPP

#include <vulkan/vulkan.h>

namespace gfxtk::backend {
    struct TextureView {
        VkImageView vulkanImageView;

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTUREVIEW_HPP
