#ifndef GFXTK_BINDGROUPENTRY_HPP
#define GFXTK_BINDGROUPENTRY_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/TextureLayout.hpp>
#include "Buffer.hpp"
#include "Sampler.hpp"
#include "TextureView.hpp"

namespace gfxtk {
    namespace backend {
        struct BindGroupEntry;
    }

    class GFXTK_EXPORT BindGroupEntry {
        friend class BindGroup;

    public:
        BindGroupEntry(Buffer& buffer, size_t offset, size_t size);
        explicit BindGroupEntry(Sampler& sampler);
        BindGroupEntry(Sampler& sampler, TextureView& textureView, TextureLayout textureLayout);
        BindGroupEntry(TextureView& textureView, TextureLayout textureLayout);
        ~BindGroupEntry();

    private:
        std::shared_ptr<backend::BindGroupEntry> _backendBindGroupEntry;

    };
}

#endif //GFXTK_BINDGROUPENTRY_HPP
