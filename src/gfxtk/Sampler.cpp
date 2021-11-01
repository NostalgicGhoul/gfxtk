#include "Sampler.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Sampler.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/Sampler.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Sampler gfxtk::Sampler::create(std::shared_ptr<backend::Device> const& backendDevice, SamplerDescriptor const& samplerDescriptor) {
    return Sampler(backend::Sampler::create(backendDevice, samplerDescriptor));
}
