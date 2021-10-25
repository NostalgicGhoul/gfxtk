#ifndef GFXTK_BACKEND_VULKAN_RENDERPASSATTACHMENT_HPP
#define GFXTK_BACKEND_VULKAN_RENDERPASSATTACHMENT_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/RenderPassAttachmentDescriptor.hpp>
#include "Device.hpp"

namespace gfxtk::backend {
    struct RenderPassAttachment {
        static std::shared_ptr<RenderPassAttachment> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                RenderPassAttachmentDescriptor const& descriptor
        );

        VkDevice vulkanDevice;
        VkRenderPass vulkanRenderPass;

        RenderPassAttachment(VkDevice vulkanDevice, VkRenderPass vulkanRenderPass)
                : vulkanDevice(vulkanDevice), vulkanRenderPass(vulkanRenderPass) {}
        ~RenderPassAttachment() {
            vkDestroyRenderPass(vulkanDevice, vulkanRenderPass, nullptr);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_RENDERPASSATTACHMENT_HPP
