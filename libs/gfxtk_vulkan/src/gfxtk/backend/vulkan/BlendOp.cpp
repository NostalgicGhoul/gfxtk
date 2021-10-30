#include <gfxtk/log.hpp>
#include "BlendOp.hpp"

VkBlendOp gfxtk::backend::BlendOp::convert(gfxtk::BlendOp blendOp) {
    switch (blendOp) {
        case gfxtk::BlendOp::Add:
            return VK_BLEND_OP_ADD;
        case gfxtk::BlendOp::Subtract:
            return VK_BLEND_OP_SUBTRACT;
        case gfxtk::BlendOp::ReverseSubtract:
            return VK_BLEND_OP_REVERSE_SUBTRACT;
        case gfxtk::BlendOp::Min:
            return VK_BLEND_OP_MIN;
        case gfxtk::BlendOp::Max:
            return VK_BLEND_OP_MAX;
        default:
            GFXTK_LOG_F("unknown `BlendOp` passed to `gfxtk::backend::BlendOp::convert`!");
    }
}
