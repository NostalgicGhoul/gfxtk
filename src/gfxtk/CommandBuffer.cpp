#include "CommandBuffer.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/CommandBuffer.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/CommandBuffer.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::CommandBuffer::CommandBuffer(std::unique_ptr<backend::CommandBuffer> backendCommandBuffer)
        : _backendCommandBuffer(std::move(backendCommandBuffer)) {}
gfxtk::CommandBuffer::~CommandBuffer() = default;

gfxtk::CommandEncoder gfxtk::CommandBuffer::beginCommandEncoding() {
    _backendCommandBuffer->beginCommandBuffer();
    return CommandEncoder::create(_backendCommandBuffer);
}
