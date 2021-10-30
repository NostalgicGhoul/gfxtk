#include <gfxtk/log.hpp>
#include "BlendFactor.hpp"

VkBlendFactor gfxtk::backend::BlendFactor::convert(gfxtk::BlendFactor blendFactor) {
    switch (blendFactor) {
        case gfxtk::BlendFactor::Zero:
            return VK_BLEND_FACTOR_ZERO;
        case gfxtk::BlendFactor::One:
            return VK_BLEND_FACTOR_ONE;
        case gfxtk::BlendFactor::SourceColor:
            return VK_BLEND_FACTOR_SRC_COLOR;
        case gfxtk::BlendFactor::OneMinusSourceColor:
            return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
        case gfxtk::BlendFactor::SourceAlpha:
            return VK_BLEND_FACTOR_SRC_ALPHA;
        case gfxtk::BlendFactor::OneMinusSourceAlpha:
            return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        case gfxtk::BlendFactor::DestinationColor:
            return VK_BLEND_FACTOR_DST_COLOR;
        case gfxtk::BlendFactor::OneMinusDestinationColor:
            return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
        case gfxtk::BlendFactor::DestinationAlpha:
            return VK_BLEND_FACTOR_DST_ALPHA;
        case gfxtk::BlendFactor::OneMinusDestinationAlpha:
            return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
        case gfxtk::BlendFactor::SourceAlphaSaturated:
            return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
        case gfxtk::BlendFactor::BlendColor:
            return VK_BLEND_FACTOR_CONSTANT_COLOR;
        case gfxtk::BlendFactor::OneMinusBlendColor:
            return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
        case gfxtk::BlendFactor::BlendAlpha:
            return VK_BLEND_FACTOR_CONSTANT_ALPHA;
        case gfxtk::BlendFactor::OneMinusBlendAlpha:
            return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
        case gfxtk::BlendFactor::Source1Color:
            return VK_BLEND_FACTOR_SRC1_COLOR;
        case gfxtk::BlendFactor::OneMinusSource1Color:
            return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
        case gfxtk::BlendFactor::Source1Alpha:
            return VK_BLEND_FACTOR_SRC1_ALPHA;
        case gfxtk::BlendFactor::OneMinusSource1Alpha:
            return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
        default:
            GFXTK_LOG_F("unknown `BlendFactor` passed to `gfxtk::backend::BlendFactor::convert`!");
    }
}
