#ifndef GFXTK_STENCILOP_HPP
#define GFXTK_STENCILOP_HPP

namespace gfxtk {
    enum class StencilOp {
        Keep,
        Zero,
        Replace,
        IncrementClamp,
        DecrementClamp,
        Invert,
        IncrementWrap,
        DecrementWrap,
    };
}

#endif //GFXTK_STENCILOP_HPP
