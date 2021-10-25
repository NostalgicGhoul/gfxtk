#ifndef GFXTK_CLEARCOLORVALUE_HPP
#define GFXTK_CLEARCOLORVALUE_HPP

#include <cstdint>
#include <array>

namespace gfxtk {
    struct ClearColorValue {
        float r;
        float g;
        float b;
        float a;

        ClearColorValue(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    };
}

#endif //GFXTK_CLEARCOLORVALUE_HPP
