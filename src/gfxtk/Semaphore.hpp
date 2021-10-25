#ifndef GFXTK_SEMAPHORE_HPP
#define GFXTK_SEMAPHORE_HPP

#include <memory>

namespace gfxtk {
    namespace backend {
        class Device;
        class Semaphore;
    }

    class Semaphore {
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
