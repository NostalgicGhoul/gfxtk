#include "Shader.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Shader.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/Shader.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Shader gfxtk::Shader::createFromSource(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::string const& sourceFilePath
) {
    return gfxtk::Shader(backend::Shader::createFromSource(backendDevice, sourceFilePath));
}

gfxtk::Shader::Shader(std::shared_ptr<backend::Shader> backendShader)
        : _backendShader(std::move(backendShader)) {}

gfxtk::Shader::~Shader() = default;
