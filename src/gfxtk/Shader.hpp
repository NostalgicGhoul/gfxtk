#ifndef GFXTK_SHADER_HPP
#define GFXTK_SHADER_HPP

#include <memory>
#include <vector>

namespace gfxtk {
    namespace backend {
        class Device;
        class Shader;
    }

    class Shader {
        friend class Device;
        friend class Pipeline;

    public:
        ~Shader();

    private:
        std::shared_ptr<backend::Shader> _backendShader;

        explicit Shader(std::shared_ptr<backend::Shader> backendShader);

        static Shader createFromSource(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::string const& sourceFilePath
        );

    };
}

#endif //GFXTK_SHADER_HPP
