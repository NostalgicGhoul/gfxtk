#ifndef GFXTK_TEXTUREVIEW_HPP
#define GFXTK_TEXTUREVIEW_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>

namespace gfxtk {
    namespace backend {
        struct TextureView;
    }

    class GFXTK_EXPORT TextureView {
        friend class BindGroupEntry;

    public:

    private:
        std::shared_ptr<backend::TextureView> _backendTextureView;

    };
}

#endif //GFXTK_TEXTUREVIEW_HPP
