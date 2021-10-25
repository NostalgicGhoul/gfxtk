#ifndef GFXTK_COLORSPACE_HPP
#define GFXTK_COLORSPACE_HPP

namespace gfxtk {
    enum class ColorSpace {
        Invalid = 0,
        SRGB,
        DisplayP3,
        ExtendedSRGB,
        ExtendedLinearSRGB,
        DCIP3,
        BT709,
        BT2020,
        AdobeRGB1998,
    };
}

#endif //GFXTK_COLORSPACE_HPP
