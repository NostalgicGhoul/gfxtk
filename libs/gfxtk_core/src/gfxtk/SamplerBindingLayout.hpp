#ifndef GFXTK_SAMPLERBINDINGLAYOUT_HPP
#define GFXTK_SAMPLERBINDINGLAYOUT_HPP

#include "microsoft_fix.hpp"

namespace gfxtk {
    enum class SamplerBindingType {
    };

    struct GFXTK_EXPORT SamplerBindingLayout {
        SamplerBindingType type;

        explicit SamplerBindingLayout(SamplerBindingType type)
                : type(type) {}

    };
}

#endif //GFXTK_SAMPLERBINDINGLAYOUT_HPP
