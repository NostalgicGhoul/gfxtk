#ifndef GFXTK_CLEARDEPTHSTENCILVALUE_HPP
#define GFXTK_CLEARDEPTHSTENCILVALUE_HPP

#include <cstdint>

namespace gfxtk {
    struct ClearDepthStencilValue {
        float depth;
        uint32_t stencil;

        ClearDepthStencilValue(float depth, uint32_t stencil) : depth(depth), stencil(stencil) {}

    };
}

#endif //GFXTK_CLEARDEPTHSTENCILVALUE_HPP
