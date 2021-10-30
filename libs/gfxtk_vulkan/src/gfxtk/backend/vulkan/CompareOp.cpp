#include <gfxtk/log.hpp>
#include "CompareOp.hpp"

VkCompareOp gfxtk::backend::CompareOp::convert(gfxtk::CompareOp compareOp) {
    switch (compareOp) {
        case gfxtk::CompareOp::Never:
            return VK_COMPARE_OP_NEVER;
        case gfxtk::CompareOp::Less:
            return VK_COMPARE_OP_LESS;
        case gfxtk::CompareOp::Equal:
            return VK_COMPARE_OP_EQUAL;
        case gfxtk::CompareOp::LessOrEqual:
            return VK_COMPARE_OP_LESS_OR_EQUAL;
        case gfxtk::CompareOp::Greater:
            return VK_COMPARE_OP_GREATER;
        case gfxtk::CompareOp::NotEqual:
            return VK_COMPARE_OP_NOT_EQUAL;
        case gfxtk::CompareOp::GreaterOrEqual:
            return VK_COMPARE_OP_GREATER_OR_EQUAL;
        case gfxtk::CompareOp::Always:
            return VK_COMPARE_OP_ALWAYS;
        default:
            GFXTK_LOG_F("unknown `CompareOp` passed to `gfxtk::backend::CompareOp::convert`!");
    }
}
