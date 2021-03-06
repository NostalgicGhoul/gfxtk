#ifndef GFXTK_BUFFER_HPP
#define GFXTK_BUFFER_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/BufferUsageFlags.hpp>
#include <gfxtk/MemoryUsage.hpp>

namespace gfxtk {
    namespace backend {
        struct Buffer;
        struct Device;
    }

    class GFXTK_EXPORT Buffer {
        friend class BindGroupEntry;
        friend class CommandEncoder;
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

        std::shared_ptr<backend::Buffer> _backendBuffer;

        explicit Buffer(std::shared_ptr<backend::Buffer> backendBuffer);

    };
}

#endif //GFXTK_BUFFER_HPP
