#ifndef GFXTK_PIPELINE_HPP
#define GFXTK_PIPELINE_HPP

#include <memory>
#include <gfxtk/gfxtk_internal.hpp>
#include "RenderPipelineDescriptor.hpp"

namespace gfxtk {
    namespace backend {
        struct Device;
        struct Pipeline;
    }

    class GFXTK_EXPORT Pipeline {
        friend class RenderPassEncoder;

    public:
        static Pipeline createRenderPipeline(
                std::shared_ptr<backend::Device> const& device,
                RenderPipelineDescriptor const& descriptor
        );

        Pipeline() : _backendPipeline(nullptr) {}
        ~Pipeline();

        [[nodiscard]]
        bool isValid() const { return _backendPipeline != nullptr; }

    private:
        std::shared_ptr<backend::Pipeline> _backendPipeline;

        explicit Pipeline(std::shared_ptr<backend::Pipeline> backendPipeline);

    };
}

#endif //GFXTK_PIPELINE_HPP
