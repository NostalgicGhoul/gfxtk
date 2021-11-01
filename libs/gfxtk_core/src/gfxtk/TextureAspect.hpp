#ifndef GFXTK_TEXTUREASPECT_HPP
#define GFXTK_TEXTUREASPECT_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class TextureAspect {
        All,
        ColorOnly,
        StencilOnly,
        DepthOnly,
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(TextureAspect);
}

#endif //GFXTK_TEXTUREASPECT_HPP
