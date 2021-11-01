#include "TextureView.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/TextureView.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/TextureView.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::TextureView gfxtk::TextureView::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::shared_ptr<backend::Texture> const& backendTexture,
        gfxtk::TextureViewType type,
        gfxtk::PixelFormat format,
        gfxtk::TextureAspect aspect
) {
    return TextureView(
            backend::TextureView::create(
                    backendDevice,
                    backendTexture,
                    type,
                    format,
                    aspect
            )
    );
}
