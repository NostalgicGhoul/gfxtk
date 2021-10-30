#ifndef GFXTK_STENCILDESCRIPTOR_HPP
#define GFXTK_STENCILDESCRIPTOR_HPP

#include "microsoft_fix.hpp"
#include <cstdint>
#include "StencilOp.hpp"
#include "CompareOp.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT StencilDescriptor {
        StencilOp stencilFailOp;
        StencilOp depthFailOp;
        StencilOp depthStencilPassOp;
        CompareOp stencilCompareOp;
        uint32_t readMask;
        uint32_t writeMask;
        uint32_t reference;

        StencilDescriptor(
                StencilOp stencilFailOp,
                StencilOp depthFailOp,
                StencilOp depthStencilPassOp,
                CompareOp stencilCompareOp,
                uint32_t readMask,
                uint32_t writeMask,
                uint32_t reference
        ) : stencilFailOp(stencilFailOp),
            depthFailOp(depthFailOp),
            depthStencilPassOp(depthStencilPassOp),
            stencilCompareOp(stencilCompareOp),
            readMask(readMask),
            writeMask(writeMask),
            reference(reference) {}

    };
}

#endif //GFXTK_STENCILDESCRIPTOR_HPP
