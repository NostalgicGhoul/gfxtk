#include "Texture.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Texture.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/Texture.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Texture gfxtk::Texture::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        gfxtk::TextureType type,
        gfxtk::PixelFormat format,
        gfxtk::Extent3D extent,
        uint32_t mipLevels,
        uint32_t arrayLayers,
        gfxtk::TextureUsage usage,
        gfxtk::MemoryUsage memoryUsage
) {
    return gfxtk::Texture(
            backend::Texture::create(
                    backendDevice,
                    type,
                    format,
                    extent,
                    mipLevels,
                    arrayLayers,
                    usage,
                    memoryUsage
            )
    );
}

gfxtk::Texture::Texture(std::shared_ptr<backend::Texture> backendTexture)
        : _backendTexture(std::move(backendTexture)) {}

gfxtk::Texture::~Texture() = default;
