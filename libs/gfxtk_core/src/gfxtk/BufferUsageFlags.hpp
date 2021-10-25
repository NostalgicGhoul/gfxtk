#ifndef GFXTK_BUFFERUSAGEFLAGS_HPP
#define GFXTK_BUFFERUSAGEFLAGS_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class BufferUsageFlags {
        Invalid = 0,
        TransferSource = 0x0001,
        TransferDestination = 0x0002,
        Uniform = 0x0010,
        Storage = 0x0020,
        Index = 0x0040,
        Vertex = 0x0080,
        Indirect = 0x0100,
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(BufferUsageFlags);
}

#endif //GFXTK_BUFFERUSAGEFLAGS_HPP
