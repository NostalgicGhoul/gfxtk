#ifndef GFXTK_SHADER_HPP
#define GFXTK_SHADER_HPP

#include <memory>
#include <vector>
#include <string>
#include <gfxtk/gfxtk_internal.hpp>

namespace gfxtk {
    namespace backend {
        struct Device;
        struct Shader;
    }

    class GFXTK_EXPORT Shader {
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
