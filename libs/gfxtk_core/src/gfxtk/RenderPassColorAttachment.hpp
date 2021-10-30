#ifndef GFXTK_RENDERPASSCOLORATTACHMENT_HPP
#define GFXTK_RENDERPASSCOLORATTACHMENT_HPP

#include "microsoft_fix.hpp"
#include "PixelFormat.hpp"
#include "LoadOp.hpp"
#include "StoreOp.hpp"
#include "TextureLayout.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT RenderPassColorAttachment {
        PixelFormat pixelFormat;
        LoadOp loadOp;
        StoreOp storeOp;
        TextureLayout initialLayout;
        TextureLayout finalLayout;

        RenderPassColorAttachment(
                PixelFormat pixelFormat,
                LoadOp loadOp,
                StoreOp storeOp,
                TextureLayout initialLayout,
                TextureLayout finalLayout
        ) : pixelFormat(pixelFormat),
            loadOp(loadOp),
            storeOp(storeOp),
            initialLayout(initialLayout),
            finalLayout(finalLayout) {}

    };
}

#endif //GFXTK_RENDERPASSCOLORATTACHMENT_HPP
