#ifndef GFXTK_TEXTUREUSAGE_HPP
#define GFXTK_TEXTUREUSAGE_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class TextureUsage {
        Invalid = 0,
        Sampled = 0x0001,
        Storage = 0x0002,
        TransferSource = 0x0004,
        TransferDestination = 0x0008,
        ColorAttachment = 0x0010,
        DepthStencilAttachment = 0x0020,
        InputAttachment = 0x0040,
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(TextureUsage);
}

#endif //GFXTK_TEXTUREUSAGE_HPP
