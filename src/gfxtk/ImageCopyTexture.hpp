#ifndef GFXTK_IMAGECOPYTEXTURE_HPP
#define GFXTK_IMAGECOPYTEXTURE_HPP

#include <gfxtk/Origin3D.hpp>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/TextureAspect.hpp>
#include <gfxtk/TextureLayout.hpp>
#include <gfxtk/PipelineStage.hpp>
#include "Texture.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT ImageCopyTexture {
        Texture const& texture;
        PipelineStage destinationStage;
        TextureLayout destinationTextureLayout;
        TextureAspect aspect;
        Origin3D origin;

        ImageCopyTexture(
                Texture const& texture,
                PipelineStage destinationStage,
                TextureLayout destinationTextureLayout,
                TextureAspect aspect = TextureAspect::All,
                Origin3D origin = {}
        ) : texture(texture),
            destinationStage(destinationStage),
            destinationTextureLayout(destinationTextureLayout),
            aspect(aspect),
            origin(origin) {}

    };
}

#endif //GFXTK_IMAGECOPYTEXTURE_HPP
