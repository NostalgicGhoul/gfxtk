#ifndef GFXTK_STORAGETEXTUREBINDINGLAYOUT_HPP
#define GFXTK_STORAGETEXTUREBINDINGLAYOUT_HPP

#include "PixelFormat.hpp"
#include "TextureViewType.hpp"

namespace gfxtk {
    enum class StorageTextureAccess {
        WriteOnly,
    };

    struct StorageTextureBindingLayout {
        StorageTextureAccess access;
        PixelFormat pixelFormat;
        TextureViewType viewType;

        StorageTextureBindingLayout(StorageTextureAccess access, PixelFormat pixelFormat, TextureViewType viewType)
                : access(access), pixelFormat(pixelFormat), viewType(viewType) {}

    };
}

#endif //GFXTK_STORAGETEXTUREBINDINGLAYOUT_HPP
