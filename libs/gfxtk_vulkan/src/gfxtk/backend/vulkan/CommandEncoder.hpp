#ifndef GFXTK_BACKEND_VULKAN_COMMANDENCODER_HPP
#define GFXTK_BACKEND_VULKAN_COMMANDENCODER_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <optional>
#include <gfxtk/ClearColorValue.hpp>
#include <gfxtk/ClearDepthStencilValue.hpp>
#include "CommandBuffer.hpp"
#include "RenderPassEncoder.hpp"
#include "Framebuffer.hpp"

namespace gfxtk::backend {
    struct CommandEncoder {
        static std::unique_ptr<CommandEncoder> create(
                std::unique_ptr<backend::CommandBuffer> const& backendCommandBuffer
        );

        VkCommandBuffer vulkanCommandBuffer;
        // If it hasn't been ended by the time it is destructed then the destructor automatically ends it.
        bool hasEnded;

        explicit CommandEncoder(VkCommandBuffer vulkanCommandBuffer)
                : vulkanCommandBuffer(vulkanCommandBuffer), hasEnded(false) {}
        ~CommandEncoder();

        std::unique_ptr<backend::RenderPassEncoder> beginRenderPass(
                std::shared_ptr<backend::RenderPassAttachment> const& renderPassAttachment,
                std::unique_ptr<backend::Framebuffer> const& framebuffer,
                Rect2D renderArea,
                std::vector<ClearColorValue> const& clearColorValues,
                std::optional<ClearDepthStencilValue> clearDepthStencilValue
        );

        void endCommandEncoding();

    };
}

#endif //GFXTK_BACKEND_VULKAN_COMMANDENCODER_HPP
