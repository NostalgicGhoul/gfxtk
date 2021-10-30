#ifndef GFXTK_EXTENT2D_HPP
#define GFXTK_EXTENT2D_HPP

#include "microsoft_fix.hpp"
#include <cstdint>

namespace gfxtk {
    struct GFXTK_EXPORT Extent2D {
        uint32_t width;
        uint32_t height;

        Extent2D() = default;
        Extent2D(uint32_t width, uint32_t height) : width(width), height(height) {}

    };
}

#endif //GFXTK_EXTENT2D_HPP
