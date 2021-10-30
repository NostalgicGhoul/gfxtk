#ifndef GFXTK_TEXTURE_HPP
#define GFXTK_TEXTURE_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>

namespace gfxtk {
    class Device;

    namespace backend {
        struct Texture;
    }

    class GFXTK_EXPORT Texture {
    public:
        static Texture create(Device const& device, std::shared_ptr<backend::Texture> backendTexture);

        ~Texture();

    private:
        std::shared_ptr<backend::Texture> _backendTexture;

        explicit Texture(std::shared_ptr<backend::Texture> backendTexture);

    };
}

#endif //GFXTK_TEXTURE_HPP
