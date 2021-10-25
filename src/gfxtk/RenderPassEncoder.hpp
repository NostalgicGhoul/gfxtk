#ifndef GFXTK_RENDERPASSENCODER_HPP
#define GFXTK_RENDERPASSENCODER_HPP

#include <memory>
#include <gfxtk/IndexType.hpp>
#include "Pipeline.hpp"
#include "Buffer.hpp"

namespace gfxtk {
    namespace backend {
        class RenderPassEncoder;
    }

    class RenderPassEncoder {
        friend class CommandEncoder;

    public:
        void setPipeline(Pipeline const& pipeline);
        void setIndexBuffer(Buffer const& buffer, IndexType type, size_t offset = 0);
        void setVertexBuffer(uint32_t binding, Buffer const& buffer, size_t offset = 0);
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
        void drawIndirect(Buffer const& buffer, size_t offset);
        void drawIndexedIndirect(Buffer const& buffer, size_t offset);
        void endRenderPass();

        ~RenderPassEncoder();

    private:
        std::unique_ptr<backend::RenderPassEncoder> _backendRenderPassEncoder;

        explicit RenderPassEncoder(std::unique_ptr<backend::RenderPassEncoder> backendRenderPassEncoder);

    };
}

#endif //GFXTK_RENDERPASSENCODER_HPP
