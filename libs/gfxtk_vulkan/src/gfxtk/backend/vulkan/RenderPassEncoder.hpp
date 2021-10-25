#ifndef GFXTK_BACKEND_VULKAN_RENDERPASSENCODER_HPP
#define GFXTK_BACKEND_VULKAN_RENDERPASSENCODER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <gfxtk/IndexType.hpp>
#include "Pipeline.hpp"
#include "Buffer.hpp"

namespace gfxtk::backend {
    struct RenderPassEncoder {
        static std::unique_ptr<RenderPassEncoder> create(VkCommandBuffer vulkanCommandBuffer);

        VkCommandBuffer vulkanCommandBuffer;
        // If it hasn't been ended by the time it is destructed then the destructor automatically ends it.
        bool hasEnded;

        explicit RenderPassEncoder(VkCommandBuffer vulkanCommandBuffer)
                : vulkanCommandBuffer(vulkanCommandBuffer), hasEnded(false) {}
        ~RenderPassEncoder();

        void setPipeline(std::shared_ptr<backend::Pipeline> const& pipeline);
        void setIndexBuffer(std::unique_ptr<backend::Buffer> const& buffer, IndexType type, size_t offset = 0);
        void setVertexBuffer(uint32_t binding, std::unique_ptr<backend::Buffer> const& buffer, size_t offset = 0);
        void draw(
                uint32_t vertexCount,
                uint32_t firstVertex = 0,
                uint32_t instanceCount = 1,
                uint32_t firstInstance = 0
        );
        void drawIndexed(
                uint32_t indexCount,
                uint32_t firstIndex = 0,
                int32_t vertexOffset = 0,
                uint32_t instanceCount = 1,
                uint32_t firstInstance = 0
        );
        void drawIndirect(std::unique_ptr<backend::Buffer> const& buffer, size_t offset);
        void drawIndexedIndirect(std::unique_ptr<backend::Buffer> const& buffer, size_t offset);
        void endRenderPass();

    };
}

#endif //GFXTK_BACKEND_VULKAN_RENDERPASSENCODER_HPP
