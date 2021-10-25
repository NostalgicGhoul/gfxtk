#include "Shader.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Shader.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Shader gfxtk::Shader::create(
        std::unique_ptr<backend::ShaderLibrary> const& backendShaderLibrary,
        std::string const& name,
        std::vector<char> const& shaderCode
) {
    return gfxtk::Shader(backend::Shader::create(backendShaderLibrary, name, shaderCode));
}

gfxtk::Shader::Shader(std::shared_ptr<backend::Shader> backendShader)
        : _backendShader(std::move(backendShader)) {}

gfxtk::Shader::~Shader() = default;
