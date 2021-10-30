#ifndef GFXTK_COMMANDENCODER_HPP
#define GFXTK_COMMANDENCODER_HPP

#include <vector>
#include <optional>
#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/Extent3D.hpp>
#include <gfxtk/Rect2D.hpp>
#include <gfxtk/ClearColorValue.hpp>
#include <gfxtk/ClearDepthStencilValue.hpp>
#include "Buffer.hpp"
#include "ImageCopyBuffer.hpp"
#include "ImageCopyTexture.hpp"
#include "RenderPassAttachment.hpp"
#include "Framebuffer.hpp"
#include "RenderPassEncoder.hpp"

namespace gfxtk {
    namespace backend {
        struct CommandBuffer;
        struct CommandEncoder;
    }

    class GFXTK_EXPORT CommandEncoder {
        friend class CommandBuffer;

    public:
        RenderPassEncoder beginRenderPass(
                RenderPassAttachment const& renderPassAttachment,
                Framebuffer const& framebuffer,
                Rect2D renderArea,
                ClearColorValue clearColorValues,
                std::optional<ClearDepthStencilValue> clearDepthStencilValue = std::nullopt
        ) {
            return beginRenderPass(
                    renderPassAttachment,
                    framebuffer,
                    renderArea,
                    std::vector<ClearColorValue>{clearColorValues},
                    clearDepthStencilValue
            );
        }
        RenderPassEncoder beginRenderPass(
                RenderPassAttachment const& renderPassAttachment,
                Framebuffer const& framebuffer,
                Rect2D renderArea,
                std::vector<ClearColorValue> const& clearColorValues,
                std::optional<ClearDepthStencilValue> clearDepthStencilValue = std::nullopt
        );

//        void copyBufferToBuffer(
//                Buffer const& source,
//                size_t sourceOffset,
//                Buffer const& destination,
//                size_t destinationOffset,
//                size_t copySize
//        );
//        void copyBufferToTexture(
//                ImageCopyBuffer const& source,
//                ImageCopyTexture const& destination,
//                Extent3D copySize
//        );
//        void copyTextureToBuffer(
//                ImageCopyTexture const& source,
//                ImageCopyBuffer const& destination,
//                Extent3D copySize
//        );
//        void copyTextureToTexture(
//                ImageCopyTexture const& source,
//                ImageCopyTexture const& destination,
//                Extent3D copySize
//        );

        void endCommandEncoding();

        ~CommandEncoder();

    private:
        static CommandEncoder create(std::unique_ptr<backend::CommandBuffer> const& backendCommandBuffer);

        std::unique_ptr<backend::CommandEncoder> _backendCommandEncoder;

        explicit CommandEncoder(std::unique_ptr<backend::CommandEncoder> backendCommandEncoder);

    };
}

#endif //GFXTK_COMMANDENCODER_HPP
