#ifndef GFXTK_PIPELINELAYOUT_HPP
#define GFXTK_PIPELINELAYOUT_HPP

#include <memory>
#include <vector>
#include "BindGroupLayout.hpp"

namespace gfxtk {
    namespace backend {
        class Device;
        class PipelineLayout;
    }

    class PipelineLayout {
        friend class Pipeline;

    public:
        static PipelineLayout create(
                std::shared_ptr<backend::Device> const& device,
                std::vector<BindGroupLayout> const& bindingGroupLayouts
        );

        PipelineLayout() : _backendPipelineLayout(nullptr) {}
        ~PipelineLayout();

    private:
        std::shared_ptr<backend::PipelineLayout> _backendPipelineLayout;

        explicit PipelineLayout(std::shared_ptr<backend::PipelineLayout> backendPipelineLayout);

    };
}

#endif //GFXTK_PIPELINELAYOUT_HPP
