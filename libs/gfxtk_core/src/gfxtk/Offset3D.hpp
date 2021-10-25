#ifndef GFXTK_OFFSET3D_HPP
#define GFXTK_OFFSET3D_HPP

#include <cstdint>

namespace gfxtk {
    struct Offset3D {
        int32_t x;
        int32_t y;
        int32_t z;

        Offset3D() = default;
        Offset3D(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}

    };
}

#endif //GFXTK_OFFSET3D_HPP
