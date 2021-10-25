#ifndef GFXTK_EXTENT3D_HPP
#define GFXTK_EXTENT3D_HPP

#include <cstdint>

namespace gfxtk {
    struct Extent3D {
        uint32_t width;
        uint32_t height;
        uint32_t depth;

        Extent3D() = default;
        Extent3D(uint32_t width, uint32_t height, uint32_t depth) : width(width), height(height), depth(depth) {}

    };
}

#endif //GFXTK_EXTENT3D_HPP
