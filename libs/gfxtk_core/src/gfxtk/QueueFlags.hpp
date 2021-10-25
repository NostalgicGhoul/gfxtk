#ifndef GFXTK_QUEUEFLAGS_HPP
#define GFXTK_QUEUEFLAGS_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class QueueFlags {
        None = 0b0000,
        Render = 0b0001,
        Compute = 0b0010,
        Present = 0b0100,
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(QueueFlags);
}

#endif //GFXTK_QUEUEFLAGS_HPP
