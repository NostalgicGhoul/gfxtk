#ifndef GFXTK_BUFFERBINDINGLAYOUT_HPP
#define GFXTK_BUFFERBINDINGLAYOUT_HPP

namespace gfxtk {
    enum class BufferBindingType {
        Uniform,
        Storage,
        ReadOnlyStorage,
    };

    struct BufferBindingLayout {
        BufferBindingType type;

        explicit BufferBindingLayout(BufferBindingType type)
                : type(type) {}

    };
}

#endif //GFXTK_BUFFERBINDINGLAYOUT_HPP
