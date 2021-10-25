#ifndef GFXTK_BLENDFACTOR_HPP
#define GFXTK_BLENDFACTOR_HPP

namespace gfxtk {
    enum class BlendFactor {
        Zero,
        One,
        SourceColor,
        OneMinusSourceColor,
        SourceAlpha,
        OneMinusSourceAlpha,
        DestinationColor,
        OneMinusDestinationColor,
        DestinationAlpha,
        OneMinusDestinationAlpha,
        SourceAlphaSaturated,
        BlendColor, // TODO: I believe this is VK_BLEND_FACTOR_CONSTANT_COLOR
        OneMinusBlendColor,
        BlendAlpha,
        OneMinusBlendAlpha,
        Source1Color,
        OneMinusSource1Color,
        Source1Alpha,
        OneMinusSource1Alpha,
    };
}

#endif //GFXTK_BLENDFACTOR_HPP
