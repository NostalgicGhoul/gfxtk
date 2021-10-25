#include "Fence.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Fence.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Fence gfxtk::Fence::create(std::shared_ptr<backend::Device> const& backendDevice, bool signaled) {
    return Fence(backend::Fence::create(backendDevice, signaled));
}

gfxtk::Fence::Fence(std::shared_ptr<backend::Fence> backendFence)
        : _backendFence(std::move(backendFence)) {}

gfxtk::Fence::~Fence() = default;
