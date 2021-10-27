#ifndef GFXTK_BUFFER_HPP
#define GFXTK_BUFFER_HPP

#include <memory>
#include <gfxtk/BufferUsageFlags.hpp>
#include <gfxtk/MemoryUsage.hpp>

namespace gfxtk {
    namespace backend {
        class Buffer;
        class Device;
    }

    class Buffer {
        friend class Device;
        friend class RenderPassEncoder;

    public:
        ~Buffer();

        void* map();
        void unmap();

    private:
        static Buffer create(
                std::shared_ptr<backend::Device> const& backendDevice,
                size_t size,
                gfxtk::BufferUsageFlags bufferUsageFlags,
                gfxtk::MemoryUsage memoryUsage
        );

        std::unique_ptr<backend::Buffer> _backendBuffer;

        explicit Buffer(std::unique_ptr<backend::Buffer> backendBuffer);

    };
}

#endif //GFXTK_BUFFER_HPP