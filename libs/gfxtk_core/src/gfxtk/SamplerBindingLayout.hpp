#ifndef GFXTK_SAMPLERBINDINGLAYOUT_HPP
#define GFXTK_SAMPLERBINDINGLAYOUT_HPP

namespace gfxtk {
    enum class SamplerBindingType {
        Filtering,
        NonFiltering,
        Comparison,
    };

    struct SamplerBindingLayout {
        SamplerBindingType type;

        explicit SamplerBindingLayout(SamplerBindingType type)
                : type(type) {}

    };
}

#endif //GFXTK_SAMPLERBINDINGLAYOUT_HPP
