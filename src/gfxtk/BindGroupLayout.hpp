#ifndef GFXTK_BINDGROUPLAYOUT_HPP
#define GFXTK_BINDGROUPLAYOUT_HPP

#include <memory>
#include <gfxtk/BindGroupLayoutDescriptor.hpp>

namespace gfxtk {
    namespace backend {
        class Device;
        class BindGroupLayout;
    }

    class BindGroupLayout {
        friend class PipelineLayout;

    public:
        static BindGroupLayout create(
                std::shared_ptr<backend::Device> const& backendDevice,
                BindGroupLayoutDescriptor const& descriptor
        );

        ~BindGroupLayout();

    private:
        std::shared_ptr<backend::BindGroupLayout> _backendBindGroupLayout;

        explicit BindGroupLayout(std::shared_ptr<backend::BindGroupLayout> backendBindGroupLayout);

    };
}

#endif //GFXTK_BINDGROUPLAYOUT_HPP
