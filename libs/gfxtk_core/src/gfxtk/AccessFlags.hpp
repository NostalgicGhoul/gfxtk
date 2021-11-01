#ifndef GFXTK_ACCESSFLAGS_HPP
#define GFXTK_ACCESSFLAGS_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class AccessFlags {
        None = 0,
        ShaderRead = 0x0001,
        ShaderWrite = 0x0002,
        ColorAttachmentRead = 0x0004,
        ColorAttachmentWrite = 0x0008,
        DepthStencilAttachmentRead = 0x0010,
        DepthStencilAttachmentWrite = 0x0020,
        TransferRead = 0x0040,
        TransferWrite = 0x0080,
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(AccessFlags);
}

#endif //GFXTK_ACCESSFLAGS_HPP
