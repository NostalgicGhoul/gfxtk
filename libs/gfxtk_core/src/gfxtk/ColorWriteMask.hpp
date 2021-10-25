#ifndef GFXTK_COLORWRITEMASK_HPP
#define GFXTK_COLORWRITEMASK_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class ColorWriteMask {
        R = 0x01,
        G = 0x02,
        B = 0x04,
        A = 0x08,
        All = R | G | B | A
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(ColorWriteMask);
}

#endif //GFXTK_COLORWRITEMASK_HPP
