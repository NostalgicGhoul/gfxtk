#ifndef GFXTK_OFFSET2D_HPP
#define GFXTK_OFFSET2D_HPP

#include <cstdint>

namespace gfxtk {
    struct Offset2D {
        int32_t x;
        int32_t y;

        Offset2D() = default;
        Offset2D(int32_t x, int32_t y) : x(x), y(y) {}

    };
}

#endif //GFXTK_OFFSET2D_HPP
