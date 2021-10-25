#ifndef GFXTK_FENCE_HPP
#define GFXTK_FENCE_HPP

#include <memory>

namespace gfxtk {
    namespace backend {
        class Device;
        class Fence;
    }

    class Fence {
        friend class CommandQueue;
        friend class Device;
        friend class SwapChain;

    public:
        ~Fence();

    private:
        static Fence create(std::shared_ptr<backend::Device> const& backendDevice, bool signaled);

        std::shared_ptr<backend::Fence> _backendFence;

        explicit Fence(std::shared_ptr<backend::Fence> backendFence);

    };
}

#endif //GFXTK_FENCE_HPP
