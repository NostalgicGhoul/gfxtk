#ifndef GFXTK_RENDERPIPELINEDESCRIPTOR_HPP
#define GFXTK_RENDERPIPELINEDESCRIPTOR_HPP

#include <optional>
#include <vector>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/PipelineVertexInputStateDescriptor.hpp>
#include <gfxtk/PrimitiveTopology.hpp>
#include <gfxtk/PipelineViewportStateDescriptor.hpp>
#include <gfxtk/PipelineRasterizationStateDescriptor.hpp>
#include <gfxtk/PipelineMultisampleStateDescriptor.hpp>
#include <gfxtk/PipelineDepthStencilStateDescriptor.hpp>
#include <gfxtk/PipelineColorBlendAttachmentDescriptor.hpp>
#include "Shader.hpp"
#include "PipelineLayout.hpp"
#include "RenderPassAttachment.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT RenderPipelineDescriptor {
        PipelineLayout pipelineLayout;
        RenderPassAttachment renderPassAttachment;
        Shader vertexShader;
        Shader fragmentShader;
        PipelineVertexInputStateDescriptor vertexInputState;
        PrimitiveTopology primitiveTopology;
        PipelineViewportStateDescriptor viewportState;
        PipelineRasterizationStateDescriptor rasterizationState;
        std::optional<PipelineMultisampleStateDescriptor> multisampleState;
        std::optional<PipelineDepthStencilStateDescriptor> depthStencilState;
        std::vector<PipelineColorBlendAttachmentDescriptor> colorBlendAttachments;

        RenderPipelineDescriptor(
                PipelineLayout pipelineLayout,
                RenderPassAttachment renderPassAttachment,
                Shader vertexShader,
                Shader fragmentShader,
                PipelineVertexInputStateDescriptor vertexInputState,
                PrimitiveTopology primitiveTopology,
                PipelineViewportStateDescriptor viewportState,
                PipelineRasterizationStateDescriptor rasterizationState,
                std::vector<PipelineColorBlendAttachmentDescriptor> colorBlendAttachments,
                std::optional<PipelineDepthStencilStateDescriptor> depthStencilState = std::nullopt,
                std::optional<PipelineMultisampleStateDescriptor> multisampleState = std::nullopt
        ) : pipelineLayout(std::move(pipelineLayout)),
            renderPassAttachment(std::move(renderPassAttachment)),
            vertexShader(std::move(vertexShader)),
            fragmentShader(std::move(fragmentShader)),
            vertexInputState(std::move(vertexInputState)),
            primitiveTopology(primitiveTopology),
            viewportState(std::move(viewportState)),
            rasterizationState(rasterizationState),
            multisampleState(multisampleState),
            depthStencilState(depthStencilState),
            colorBlendAttachments(std::move(colorBlendAttachments)) {}

    };
}

#endif //GFXTK_RENDERPIPELINEDESCRIPTOR_HPP
