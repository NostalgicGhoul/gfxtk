#include "Buffer.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Buffer.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/Buffer.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Buffer gfxtk::Buffer::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        size_t size,
        gfxtk::BufferUsageFlags bufferUsageFlags,
        gfxtk::MemoryUsage memoryUsage
) {
    return Buffer(backend::Buffer::create(backendDevice, size, bufferUsageFlags, memoryUsage));
}

gfxtk::Buffer::Buffer(std::unique_ptr<backend::Buffer> backendBuffer)
        : _backendBuffer(std::move(backendBuffer)) {}

gfxtk::Buffer::Buffer(Buffer&& other) noexcept {
    this->_backendBuffer = std::move(other._backendBuffer);
}

gfxtk::Buffer& gfxtk::Buffer::operator=(Buffer&& other) noexcept {
    this->_backendBuffer = std::move(other._backendBuffer);
    return *this;
}

gfxtk::Buffer::~Buffer() = default;

void* gfxtk::Buffer::map() {
    return _backendBuffer->map();
}

void gfxtk::Buffer::unmap() {
    _backendBuffer->unmap();
}
