#include "ShaderLibrary.hpp"

std::unique_ptr<gfxtk::backend::ShaderLibrary> gfxtk::backend::ShaderLibrary::create(
        std::shared_ptr<backend::Device> const& backendDevice
) {
    return std::make_unique<ShaderLibrary>(backendDevice->logicalDevice);
}
