#ifndef GFXTK_BACKEND_VULKAN_COMMANDENCODER_HPP
#define GFXTK_BACKEND_VULKAN_COMMANDENCODER_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <optional>
#include <gfxtk/ClearColorValue.hpp>
#include <gfxtk/ClearDepthStencilValue.hpp>
#include <gfxtk/TextureAspect.hpp>
#include <gfxtk/Origin3D.hpp>
#include <gfxtk/AccessFlags.hpp>
#include "CommandBuffer.hpp"
#include "RenderPassEncoder.hpp"
#include "Framebuffer.hpp"
#include "Texture.hpp"
#include "PipelineStage.hpp"

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

        void copyBufferToBuffer(
                std::shared_ptr<backend::Buffer> const& source,
                size_t sourceOffset,
                std::shared_ptr<backend::Buffer> const& destination,
                size_t destinationOffset,
                size_t copySize
        );

        void copyBufferToTexture(
                std::shared_ptr<backend::Buffer> const& buffer,
                size_t offset,
                uint32_t bytesPerRow,
                uint32_t rowsPerImage,
                std::shared_ptr<backend::Texture> const& texture,
                gfxtk::PipelineStage destinationStage,
                gfxtk::TextureLayout destinationTextureLayout,
                gfxtk::Origin3D origin,
                gfxtk::TextureAspect aspect,
                Extent3D copySize
        );

        void endCommandEncoding();

    };
}

#endif //GFXTK_BACKEND_VULKAN_COMMANDENCODER_HPP
