#ifndef GFXTK_SHADER_HPP
#define GFXTK_SHADER_HPP

#include <memory>
#include <vector>

namespace gfxtk {
    namespace backend {
        class Shader;
        class ShaderLibrary;
    }

    class Shader {
        friend class ShaderLibrary;
        friend class Pipeline;

    public:
        ~Shader();

    private:
        std::shared_ptr<backend::Shader> _backendShader;

        explicit Shader(std::shared_ptr<backend::Shader> backendShader);

        static Shader create(
                std::unique_ptr<backend::ShaderLibrary> const& backendShaderLibrary,
                std::string const& name,
                std::vector<char> const& shaderCode
        );

    };
}

#endif //GFXTK_SHADER_HPP
