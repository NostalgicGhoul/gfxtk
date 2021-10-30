#ifndef GFXTK_ORIGIN3D_HPP
#define GFXTK_ORIGIN3D_HPP

#include "microsoft_fix.hpp"
#include <cstdint>

namespace gfxtk {
    struct GFXTK_EXPORT Origin3D {
        uint32_t x;
        uint32_t y;
        uint32_t z;

        Origin3D() = default;
        Origin3D(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) {}

    };
}

#endif //GFXTK_ORIGIN3D_HPP
