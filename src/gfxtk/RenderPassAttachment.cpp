#include "RenderPassAttachment.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/RenderPassAttachment.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/RenderPassAttachment.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::RenderPassAttachment gfxtk::RenderPassAttachment::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        gfxtk::RenderPassAttachmentDescriptor const& descriptor
) {
    return gfxtk::RenderPassAttachment(gfxtk::backend::RenderPassAttachment::create(backendDevice, descriptor));
}
gfxtk::RenderPassAttachment::RenderPassAttachment(
        std::shared_ptr<backend::RenderPassAttachment> backendRenderPassAttachment
) : _backendRenderPassAttachment(std::move(backendRenderPassAttachment)) {}

gfxtk::RenderPassAttachment::~RenderPassAttachment() = default;
