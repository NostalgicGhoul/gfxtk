#include "BindGroupLayout.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/BindGroupLayout.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/BindGroupLayout.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::BindGroupLayout gfxtk::BindGroupLayout::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        gfxtk::BindGroupLayoutDescriptor const& descriptor
) {
    return gfxtk::BindGroupLayout(
            backend::BindGroupLayout::create(backendDevice, descriptor)
    );
}

gfxtk::BindGroupLayout::BindGroupLayout(std::shared_ptr<backend::BindGroupLayout> backendBindGroupLayout)
        : _backendBindGroupLayout(std::move(backendBindGroupLayout)) {}

gfxtk::BindGroupLayout::~BindGroupLayout() = default;
