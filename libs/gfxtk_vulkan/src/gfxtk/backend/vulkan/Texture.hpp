#ifndef GFXTK_BACKEND_VULKAN_TEXTURE_HPP
#define GFXTK_BACKEND_VULKAN_TEXTURE_HPP

#include <vulkan/vulkan.h>
#include <memory>

namespace gfxtk::backend {
    struct Texture {
        static std::shared_ptr<Texture> createRefOnly(VkImage vulkanImage);

        // NOTE: If this is null then we don't destroy the image. This is only useful for images we get from the swap
        //       chain as the swap chain owns those images.
        VkDevice vulkanDevice;
        VkImage vulkanImage;

        Texture(VkDevice vulkanDevice, VkImage vulkanImage)
                : vulkanDevice(vulkanDevice), vulkanImage(vulkanImage) {}
        ~Texture();

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTURE_HPP
