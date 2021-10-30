#ifndef GFXTK_OFFSET3D_HPP
#define GFXTK_OFFSET3D_HPP

#include "microsoft_fix.hpp"
#include <cstdint>

namespace gfxtk {
    struct GFXTK_EXPORT Offset3D {
        int32_t x;
        int32_t y;
        int32_t z;

        Offset3D() = default;
        Offset3D(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}

    };
}

#endif //GFXTK_OFFSET3D_HPP
