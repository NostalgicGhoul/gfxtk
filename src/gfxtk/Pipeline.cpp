#include "Pipeline.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Pipeline.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/Pipeline.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::Pipeline gfxtk::Pipeline::createRenderPipeline(
        std::shared_ptr<backend::Device> const& device,
        gfxtk::RenderPipelineDescriptor const& descriptor
) {
    return gfxtk::Pipeline(
            backend::Pipeline::createRenderPipeline(
                    device,
                    descriptor.vertexShader._backendShader,
                    descriptor.fragmentShader._backendShader,
                    descriptor.vertexInputState,
                    descriptor.primitiveTopology,
                    descriptor.viewportState,
                    descriptor.rasterizationState,
                    descriptor.multisampleState,
                    descriptor.depthStencilState,
                    descriptor.colorBlendAttachments,
                    descriptor.pipelineLayout._backendPipelineLayout,
                    descriptor.renderPassAttachment._backendRenderPassAttachment
            )
    );
}

gfxtk::Pipeline::Pipeline(std::shared_ptr<backend::Pipeline> backendPipeline)
        : _backendPipeline(std::move(backendPipeline)) {}

gfxtk::Pipeline::~Pipeline() = default;
