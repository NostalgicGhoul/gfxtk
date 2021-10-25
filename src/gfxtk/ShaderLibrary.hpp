#ifndef GFXTK_SHADERLIBRARY_HPP
#define GFXTK_SHADERLIBRARY_HPP

#include <memory>
#include "Shader.hpp"

namespace gfxtk {
    namespace backend {
        class Device;
        class ShaderLibrary;
    }

    class ShaderLibrary {
        friend class Device;

    public:
        Shader createShader(std::string const& name, std::vector<char> const& shaderCode);

        // REMINDER: This is set to `default` in `SharedLibrary.cpp`. This is on purpose because C++ will create an
        //           _inline_ destructor for `ShaderLibrary` if you don't declare it in a `.cpp` file. This then causes
        //           issues from the fact that `backend::ShaderLibrary` is incomplete. The destructor is the only thing
        //           that has to know the full type for `backend::ShaderLibrary`
        // TL;DR: Don't delete this even though it is just `default`. This is required.
        ~ShaderLibrary();

    private:
        std::unique_ptr<backend::ShaderLibrary> _backendShaderLibrary;

        explicit ShaderLibrary(std::unique_ptr<backend::ShaderLibrary> backendShaderLibrary);

        static ShaderLibrary create(std::shared_ptr<backend::Device> const& backendDevice);

    };
}

#endif //GFXTK_SHADERLIBRARY_HPP
