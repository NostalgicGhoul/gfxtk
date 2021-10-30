#ifndef GFXTK_RENDERPASSATTACHMENT_HPP
#define GFXTK_RENDERPASSATTACHMENT_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/RenderPassAttachmentDescriptor.hpp>

namespace gfxtk {
    namespace backend {
        struct Device;
        struct RenderPassAttachment;
    }

    class GFXTK_EXPORT RenderPassAttachment {
        friend class Pipeline;
        friend class SwapChain;
        friend class CommandEncoder;

    public:
        static RenderPassAttachment create(
                std::shared_ptr<backend::Device> const& backendDevice,
                RenderPassAttachmentDescriptor const& descriptor
        );

        RenderPassAttachment() : _backendRenderPassAttachment(nullptr) {}
        ~RenderPassAttachment();

        [[nodiscard]]
        bool isValid() const { return _backendRenderPassAttachment != nullptr; }

    private:
        std::shared_ptr<backend::RenderPassAttachment> _backendRenderPassAttachment;

        explicit RenderPassAttachment(std::shared_ptr<backend::RenderPassAttachment> backendRenderPassAttachment);

    };
}

#endif //GFXTK_RENDERPASSATTACHMENT_HPP
