#ifndef GFXTK_BACKEND_VULKAN_TEXTURELAYOUT_HPP
#define GFXTK_BACKEND_VULKAN_TEXTURELAYOUT_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/TextureLayout.hpp>

namespace gfxtk::backend {
    struct TextureLayout {
        static VkImageLayout convert(gfxtk::TextureLayout textureLayout);

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTURELAYOUT_HPP
