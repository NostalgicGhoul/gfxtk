#ifndef GFXTK_TEXTUREBINDINGLAYOUT_HPP
#define GFXTK_TEXTUREBINDINGLAYOUT_HPP

#include "microsoft_fix.hpp"
#include "TextureViewType.hpp"

namespace gfxtk {
    enum class TextureSampleType {
        Float,
        UnfilterableFloat,
        Depth,
        Sint,
        Uint,
    };

    struct GFXTK_EXPORT TextureBindingLayout {
        TextureSampleType sampleType;
        TextureViewType viewType;
        bool multisampled;

        TextureBindingLayout(TextureSampleType sampleType, TextureViewType viewType, bool multisampled)
                : sampleType(sampleType), viewType(viewType), multisampled(multisampled) {}

    };
}

#endif //GFXTK_TEXTUREBINDINGLAYOUT_HPP
