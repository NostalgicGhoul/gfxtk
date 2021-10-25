#ifndef GFXTK_ORIGIN3D_HPP
#define GFXTK_ORIGIN3D_HPP

#include <cstdint>

namespace gfxtk {
    struct Origin3D {
        uint32_t x;
        uint32_t y;
        uint32_t z;

        Origin3D() = default;
        Origin3D(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) {}

    };
}

#endif //GFXTK_ORIGIN3D_HPP
