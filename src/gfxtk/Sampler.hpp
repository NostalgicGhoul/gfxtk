#ifndef GFXTK_SAMPLER_HPP
#define GFXTK_SAMPLER_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>

namespace gfxtk {
    namespace backend {
        struct Sampler;
    }

    class GFXTK_EXPORT Sampler {
        friend class BindGroupEntry;

    public:

    private:
        std::shared_ptr<backend::Sampler> _backendSampler;

    };
}

#endif //GFXTK_SAMPLER_HPP
