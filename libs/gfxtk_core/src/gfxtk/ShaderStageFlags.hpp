#ifndef GFXTK_SHADERSTAGEFLAGS_HPP
#define GFXTK_SHADERSTAGEFLAGS_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class ShaderStageFlags {
        Vertex = 0x1,
        Fragment = 0x2,
        Compute = 0x4,
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(ShaderStageFlags);
}

#endif //GFXTK_SHADERSTAGEFLAGS_HPP
