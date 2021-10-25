#include "Texture.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Texture.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Texture gfxtk::Texture::create(gfxtk::Device const& device, std::shared_ptr<backend::Texture> backendTexture) {
    return gfxtk::Texture(std::move(backendTexture));
}

gfxtk::Texture::Texture(std::shared_ptr<backend::Texture> backendTexture)
        : _backendTexture(std::move(backendTexture)) {}

gfxtk::Texture::~Texture() = default;
