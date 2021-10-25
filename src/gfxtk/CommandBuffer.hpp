#ifndef GFXTK_COMMANDBUFFER_HPP
#define GFXTK_COMMANDBUFFER_HPP

#include <memory>
#include "CommandEncoder.hpp"

namespace gfxtk {
    namespace backend {
        class CommandBuffer;
    }

    class CommandBuffer {
        friend class CommandQueue;

    public:
        ~CommandBuffer();

        CommandEncoder beginCommandEncoding();

    private:
        std::unique_ptr<backend::CommandBuffer> _backendCommandBuffer;

        explicit CommandBuffer(std::unique_ptr<backend::CommandBuffer> backendCommandBuffer);

    };
}

#endif //GFXTK_COMMANDBUFFER_HPP
