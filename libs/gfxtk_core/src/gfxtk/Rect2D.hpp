#ifndef GFXTK_RECT2D_HPP
#define GFXTK_RECT2D_HPP

#include "Offset2D.hpp"
#include "Extent2D.hpp"

namespace gfxtk {
    struct Rect2D {
        Offset2D offset;
        Extent2D extent;

        Rect2D() = default;
        Rect2D(Offset2D offset, Extent2D extent) : offset(offset), extent(extent) {}
        Rect2D(int32_t x, int32_t y, Extent2D extent) : offset(x, y), extent(extent) {}
        Rect2D(Offset2D offset, uint32_t width, uint32_t height) : offset(offset), extent(width, height) {}
        Rect2D(int32_t x, int32_t y, uint32_t width, uint32_t height) : offset(x, y), extent(width, height) {}

    };
}

#endif //GFXTK_RECT2D_HPP
