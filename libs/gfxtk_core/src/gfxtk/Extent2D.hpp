#ifndef GFXTK_EXTENT2D_HPP
#define GFXTK_EXTENT2D_HPP

#include <cstdint>

namespace gfxtk {
    struct Extent2D {
        uint32_t width;
        uint32_t height;

        Extent2D() = default;
        Extent2D(uint32_t width, uint32_t height) : width(width), height(height) {}

    };
}

#endif //GFXTK_EXTENT2D_HPP
