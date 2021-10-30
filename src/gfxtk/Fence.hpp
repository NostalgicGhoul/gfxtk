#ifndef GFXTK_FENCE_HPP
#define GFXTK_FENCE_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>

namespace gfxtk {
    namespace backend {
        struct Device;
        struct Fence;
    }

    class GFXTK_EXPORT Fence {
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
