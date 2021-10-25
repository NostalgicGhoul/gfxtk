#ifndef GFXTK_BACKEND_VULKAN_SHADERLIBRARY_HPP
#define GFXTK_BACKEND_VULKAN_SHADERLIBRARY_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include "Device.hpp"

namespace gfxtk::backend {
    // `ShaderLibrary` is more of a compatibility feature for Metal. Metal uses `MTLLibrary` and `MTLFunction` for
    // shaders with `MTLFunction` being basically `VkShaderModule`. Because of `MTLLibrary`, I've decided to create
    // `ShaderLibrary` which, for the Vulkan backend, just holds a reference to `VkDevice` so you can create a `Shader`
    // from just a `ShaderLibrary`.
    struct ShaderLibrary {
        static std::unique_ptr<ShaderLibrary> create(std::shared_ptr<backend::Device> const& backendDevice);

        VkDevice vulkanDevice;

        explicit ShaderLibrary(VkDevice vulkanDevice)
                : vulkanDevice(vulkanDevice) {}

    };
}

#endif //GFXTK_BACKEND_VULKAN_SHADERLIBRARY_HPP
