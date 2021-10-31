#include "BindGroupEntry.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/BindGroupEntry.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/BindGroupEntry.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::BindGroupEntry::BindGroupEntry(gfxtk::Buffer& buffer, size_t offset, size_t size)
        : _backendBindGroupEntry(backend::BindGroupEntry::create(buffer._backendBuffer.get(), offset, size)) {}
gfxtk::BindGroupEntry::BindGroupEntry(gfxtk::Sampler& sampler)
        : _backendBindGroupEntry(backend::BindGroupEntry::create(sampler._backendSampler.get())) {}
gfxtk::BindGroupEntry::BindGroupEntry(gfxtk::TextureView& textureView, gfxtk::TextureLayout textureLayout)
        : _backendBindGroupEntry(backend::BindGroupEntry::create(textureView._backendTextureView.get(), textureLayout)) {}

gfxtk::BindGroupEntry::~BindGroupEntry() = default;
