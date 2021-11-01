#ifndef GFXTK_BACKEND_VULKAN_TEXTUREVIEW_HPP
#define GFXTK_BACKEND_VULKAN_TEXTUREVIEW_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/TextureViewType.hpp>
#include <gfxtk/TextureAspect.hpp>
#include "Texture.hpp"

namespace gfxtk::backend {
    struct TextureView {
        static std::shared_ptr<TextureView> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::shared_ptr<backend::Texture> const& backendTexture,
                gfxtk::TextureViewType type,
                gfxtk::PixelFormat format,
                gfxtk::TextureAspect aspect
        );

        VkDevice vulkanDevice;
        VkImageView vulkanImageView;

        TextureView(VkDevice vulkanDevice, VkImageView vulkanImageView)
                : vulkanDevice(vulkanDevice), vulkanImageView(vulkanImageView) {}
        ~TextureView() {
            vkDestroyImageView(vulkanDevice, vulkanImageView, nullptr);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_TEXTUREVIEW_HPP
