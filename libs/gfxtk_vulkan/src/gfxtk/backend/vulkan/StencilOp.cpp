#include <gfxtk/log.hpp>
#include "StencilOp.hpp"

VkStencilOp gfxtk::backend::StencilOp::convert(gfxtk::StencilOp stencilOp) {
    switch (stencilOp) {
        case gfxtk::StencilOp::Keep:
            return VK_STENCIL_OP_KEEP;
        case gfxtk::StencilOp::Zero:
            return VK_STENCIL_OP_ZERO;
        case gfxtk::StencilOp::Replace:
            return VK_STENCIL_OP_REPLACE;
        case gfxtk::StencilOp::IncrementClamp:
            return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
        case gfxtk::StencilOp::DecrementClamp:
            return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
        case gfxtk::StencilOp::Invert:
            return VK_STENCIL_OP_INVERT;
        case gfxtk::StencilOp::IncrementWrap:
            return VK_STENCIL_OP_INCREMENT_AND_WRAP;
        case gfxtk::StencilOp::DecrementWrap:
            return VK_STENCIL_OP_DECREMENT_AND_WRAP;
        default:
            GFXTK_LOG_F("unknown `StencilOp` found in `gfxtk::backend::StencilOp::convert`!");
    }
}
