#ifndef GFXTK_TEXTUREVIEW_HPP
#define GFXTK_TEXTUREVIEW_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/TextureViewType.hpp>
#include <gfxtk/PixelFormat.hpp>
#include <gfxtk/TextureAspect.hpp>

namespace gfxtk {
    namespace backend {
        struct Device;
        struct Texture;
        struct TextureView;
    }

    class GFXTK_EXPORT TextureView {
        friend class BindGroupEntry;
        friend class Device;

    public:

    private:
        static TextureView create(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::shared_ptr<backend::Texture> const& backendTexture,
                gfxtk::TextureViewType type,
                gfxtk::PixelFormat format,
                gfxtk::TextureAspect aspect
        );

        std::shared_ptr<backend::TextureView> _backendTextureView;

        explicit TextureView(std::shared_ptr<backend::TextureView> backendTextureView)
                : _backendTextureView(std::move(backendTextureView)) {}

    };
}

#endif //GFXTK_TEXTUREVIEW_HPP
