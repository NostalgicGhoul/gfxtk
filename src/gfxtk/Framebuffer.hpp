#ifndef GFXTK_FRAMEBUFFER_HPP
#define GFXTK_FRAMEBUFFER_HPP

#include <memory>
#include <gfxtk/FramebufferErrors.hpp>

namespace gfxtk {
    namespace backend {
        class Framebuffer;
    }

    class Framebuffer {
        friend class CommandEncoder;
        friend class CommandQueue;
        friend class SwapChain;

    public:
        ~Framebuffer();

        [[nodiscard]]
        bool hasErrors() const { return _frameBufferErrors == FramebufferErrors::None; }
        [[nodiscard]]
        FramebufferErrors frameBufferErrors() const { return _frameBufferErrors; }

    private:
        std::unique_ptr<backend::Framebuffer> _backendFramebuffer;
        FramebufferErrors _frameBufferErrors;

        Framebuffer(std::unique_ptr<backend::Framebuffer> backendFramebuffer, FramebufferErrors frameBufferErrors);

    };
}

#endif //GFXTK_FRAMEBUFFER_HPP
