#ifndef GFXTK_SAMPLER_HPP
#define GFXTK_SAMPLER_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/SamplerDescriptor.hpp>

namespace gfxtk {
    namespace backend {
        struct Device;
        struct Sampler;
    }

    class GFXTK_EXPORT Sampler {
        friend class BindGroupEntry;
        friend class Device;

    public:

    private:
        static Sampler create(
                std::shared_ptr<backend::Device> const& backendDevice,
                SamplerDescriptor const& samplerDescriptor
        );

        std::shared_ptr<backend::Sampler> _backendSampler;

        explicit Sampler(std::shared_ptr<backend::Sampler> backendSampler)
                : _backendSampler(std::move(backendSampler)) {}

    };
}

#endif //GFXTK_SAMPLER_HPP
