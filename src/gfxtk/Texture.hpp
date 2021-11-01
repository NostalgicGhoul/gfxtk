#ifndef GFXTK_TEXTURE_HPP
#define GFXTK_TEXTURE_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/TextureType.hpp>
#include <gfxtk/TextureUsage.hpp>
#include <gfxtk/PixelFormat.hpp>
#include <gfxtk/Extent3D.hpp>
#include <gfxtk/MemoryUsage.hpp>

namespace gfxtk {
    class Device;

    namespace backend {
        struct Device;
        struct Texture;
    }

    class GFXTK_EXPORT Texture {
        friend class CommandEncoder;
        friend class Device;

    public:
        static Texture create(
                std::shared_ptr<backend::Device> const& backendDevice,
                gfxtk::TextureType type,
                gfxtk::PixelFormat format,
                gfxtk::Extent3D extent,
                uint32_t mipLevels,
                uint32_t arrayLayers,
                gfxtk::TextureUsage usage,
                gfxtk::MemoryUsage memoryUsage
        );

        ~Texture();

    private:
        std::shared_ptr<backend::Texture> _backendTexture;

        explicit Texture(std::shared_ptr<backend::Texture> backendTexture);

    };
}

#endif //GFXTK_TEXTURE_HPP
