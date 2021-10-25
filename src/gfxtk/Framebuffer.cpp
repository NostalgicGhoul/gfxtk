#include "Framebuffer.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Framebuffer.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Framebuffer::Framebuffer(
        std::unique_ptr<backend::Framebuffer> backendFramebuffer,
        FramebufferErrors frameBufferErrors
) : _backendFramebuffer(std::move(backendFramebuffer)), _frameBufferErrors(frameBufferErrors) {}

gfxtk::Framebuffer::~Framebuffer() = default;
