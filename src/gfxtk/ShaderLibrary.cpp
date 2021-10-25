#include "ShaderLibrary.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/ShaderLibrary.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::ShaderLibrary gfxtk::ShaderLibrary::create(std::shared_ptr<backend::Device> const& backendDevice) {
    return gfxtk::ShaderLibrary(backend::ShaderLibrary::create(backendDevice));
}

gfxtk::ShaderLibrary::ShaderLibrary(std::unique_ptr<backend::ShaderLibrary> backendShaderLibrary)
        : _backendShaderLibrary(std::move(backendShaderLibrary)) {}

gfxtk::Shader gfxtk::ShaderLibrary::createShader(std::string const& name, std::vector<char> const& shaderCode) {
    return gfxtk::Shader(Shader::create(_backendShaderLibrary, name, shaderCode));
}

gfxtk::ShaderLibrary::~ShaderLibrary() = default;
