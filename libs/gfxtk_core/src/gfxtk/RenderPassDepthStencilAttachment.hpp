#ifndef GFXTK_RENDERPASSDEPTHSTENCILATTACHMENT_HPP
#define GFXTK_RENDERPASSDEPTHSTENCILATTACHMENT_HPP

#include "microsoft_fix.hpp"
#include "PixelFormat.hpp"
#include "LoadOp.hpp"
#include "StoreOp.hpp"
#include "TextureLayout.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT RenderPassDepthStencilAttachment {
        PixelFormat pixelFormat;
        LoadOp depthLoadOp;
        StoreOp depthStoreOp;
        LoadOp stencilLoadOp;
        StoreOp stencilStoreOp;
        TextureLayout initialLayout;
        TextureLayout finalLayout;

        RenderPassDepthStencilAttachment(
                PixelFormat pixelFormat,
                LoadOp depthLoadOp,
                StoreOp depthStoreOp,
                LoadOp stencilLoadOp,
                StoreOp stencilStoreOp,
                TextureLayout initialLayout,
                TextureLayout finalLayout
        ) : pixelFormat(pixelFormat),
            depthLoadOp(depthLoadOp),
            depthStoreOp(depthStoreOp),
            stencilLoadOp(stencilLoadOp),
            stencilStoreOp(stencilStoreOp),
            initialLayout(initialLayout),
            finalLayout(finalLayout) {}

    };
}

#endif //GFXTK_RENDERPASSDEPTHSTENCILATTACHMENT_HPP
