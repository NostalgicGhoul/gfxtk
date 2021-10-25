#include "Semaphore.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Semaphore.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Semaphore::Semaphore(std::shared_ptr<backend::Semaphore> backendSemaphore)
        : _backendSemaphore(std::move(backendSemaphore)) {}

gfxtk::Semaphore::~Semaphore() = default;

gfxtk::Semaphore gfxtk::Semaphore::create(std::shared_ptr<backend::Device> const& backendDevice) {
    return gfxtk::Semaphore(backend::Semaphore::create(backendDevice));
}
