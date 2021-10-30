#ifndef GFXTK_EXTENT3D_HPP
#define GFXTK_EXTENT3D_HPP

#include "microsoft_fix.hpp"
#include <cstdint>

namespace gfxtk {
    struct GFXTK_EXPORT Extent3D {
        uint32_t width;
        uint32_t height;
        uint32_t depth;

        Extent3D() = default;
        Extent3D(uint32_t width, uint32_t height, uint32_t depth) : width(width), height(height), depth(depth) {}

    };
}

#endif //GFXTK_EXTENT3D_HPP
