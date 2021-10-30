#ifndef GFXTK_CLEARDEPTHSTENCILVALUE_HPP
#define GFXTK_CLEARDEPTHSTENCILVALUE_HPP

#include "microsoft_fix.hpp"
#include <cstdint>

namespace gfxtk {
    struct GFXTK_EXPORT ClearDepthStencilValue {
        float depth;
        uint32_t stencil;

        ClearDepthStencilValue(float depth, uint32_t stencil) : depth(depth), stencil(stencil) {}

    };
}

#endif //GFXTK_CLEARDEPTHSTENCILVALUE_HPP
