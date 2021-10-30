#ifndef GFXTK_BUFFERBINDINGLAYOUT_HPP
#define GFXTK_BUFFERBINDINGLAYOUT_HPP

#include "microsoft_fix.hpp"

namespace gfxtk {
    enum class BufferBindingType {
        Uniform,
        Storage,
        ReadOnlyStorage,
    };

    struct GFXTK_EXPORT BufferBindingLayout {
        BufferBindingType type;

        explicit BufferBindingLayout(BufferBindingType type)
                : type(type) {}

    };
}

#endif //GFXTK_BUFFERBINDINGLAYOUT_HPP
