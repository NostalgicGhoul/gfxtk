#ifndef GFXTK_CLEARCOLORVALUE_HPP
#define GFXTK_CLEARCOLORVALUE_HPP

#include "microsoft_fix.hpp"
#include <cstdint>
#include <array>

namespace gfxtk {
    struct GFXTK_EXPORT ClearColorValue {
        float r;
        float g;
        float b;
        float a;

        ClearColorValue(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    };
}

#endif //GFXTK_CLEARCOLORVALUE_HPP
