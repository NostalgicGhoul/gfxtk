#ifndef GFXTK_IMAGECOPYTEXTURE_HPP
#define GFXTK_IMAGECOPYTEXTURE_HPP

#include <gfxtk/Origin3D.hpp>
#include <gfxtk/TextureAspect.hpp>
#include "Texture.hpp"

namespace gfxtk {
    struct ImageCopyTexture {
        Texture texture;
        uint32_t mipLevel;
        Origin3D origin;
        TextureAspect aspect;

        explicit ImageCopyTexture(
                Texture texture,
                uint32_t mipLevel = 0,
                Origin3D origin = {},
                TextureAspect aspect = TextureAspect::All
        ) : texture(std::move(texture)), mipLevel(mipLevel), origin(origin), aspect(aspect) {}

    };
}

#endif //GFXTK_IMAGECOPYTEXTURE_HPP
