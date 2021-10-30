#ifndef GFXTK_SEMAPHORE_HPP
#define GFXTK_SEMAPHORE_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>

namespace gfxtk {
    namespace backend {
        struct Device;
        struct Semaphore;
    }

    class GFXTK_EXPORT Semaphore {
        friend class CommandQueue;
        friend class Device;
        friend class SwapChain;

    public:
        ~Semaphore();

    private:
        static Semaphore create(std::shared_ptr<backend::Device> const& backendDevice);

        std::shared_ptr<backend::Semaphore> _backendSemaphore;

        explicit Semaphore(std::shared_ptr<backend::Semaphore> backendSemaphore);

    };
}

#endif //GFXTK_SEMAPHORE_HPP
