#ifndef GFXTK_RENDERPASSATTACHMENTDESCRIPTOR_HPP
#define GFXTK_RENDERPASSATTACHMENTDESCRIPTOR_HPP

#include <vector>
#include <optional>
#include "RenderPassColorAttachment.hpp"
#include "RenderPassDepthStencilAttachment.hpp"

namespace gfxtk {
    struct RenderPassAttachmentDescriptor {
        std::vector<RenderPassColorAttachment> colorAttachments;
        std::optional<RenderPassDepthStencilAttachment> depthStencilAttachment;

        explicit RenderPassAttachmentDescriptor(
                std::vector<RenderPassColorAttachment> colorAttachments,
                std::optional<RenderPassDepthStencilAttachment> depthStencilAttachment = std::nullopt
        ) : colorAttachments(std::move(colorAttachments)),
            depthStencilAttachment(depthStencilAttachment) {}

    };
}

#endif //GFXTK_RENDERPASSATTACHMENTDESCRIPTOR_HPP
