#include <gfxtk/log.hpp>
#include "Pipeline.hpp"
#include "VertexFormat.hpp"
#include "PrimitiveTopology.hpp"
#include "TriangleFillMode.hpp"
#include "CullMode.hpp"
#include "SampleCount.hpp"
#include "BlendFactor.hpp"
#include "BlendOp.hpp"
#include "ColorWriteMask.hpp"
#include "CompareOp.hpp"
#include "StencilOp.hpp"

std::shared_ptr<gfxtk::backend::Pipeline> gfxtk::backend::Pipeline::createRenderPipeline(
        std::shared_ptr<backend::Device> const& device,
        std::shared_ptr<backend::Shader> const& vertexShader,
        std::shared_ptr<backend::Shader> const& fragmentShader,
        gfxtk::PipelineVertexInputStateDescriptor const& vertexInputState,
        gfxtk::PrimitiveTopology primitiveTopology,
        gfxtk::PipelineViewportStateDescriptor const& viewportState,
        gfxtk::PipelineRasterizationStateDescriptor const& rasterizationState,
        std::optional<PipelineMultisampleStateDescriptor> const& multisampleState,
        std::optional<gfxtk::PipelineDepthStencilStateDescriptor> const& depthStencilState,
        std::vector<PipelineColorBlendAttachmentDescriptor> const& colorBlendAttachments,
        std::shared_ptr<backend::PipelineLayout> const& pipelineLayout,
        std::shared_ptr<backend::RenderPassAttachment> const& renderPassAttachment
) {
    VkPipelineShaderStageCreateInfo vertexShaderStageInfo{};
    vertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertexShaderStageInfo.module = vertexShader->vulkanShader;
    vertexShaderStageInfo.pName = "main";
    VkPipelineShaderStageCreateInfo fragmentShaderStageInfo{};
    fragmentShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragmentShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragmentShaderStageInfo.module = fragmentShader->vulkanShader;
    fragmentShaderStageInfo.pName = "main";
    std::vector<VkPipelineShaderStageCreateInfo> vulkanShaderStages = {vertexShaderStageInfo, fragmentShaderStageInfo};

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = backend::PrimitiveTopology::convertToVkPrimitiveTopology(primitiveTopology);
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    vertexBindingDescriptions.reserve(vertexInputState.buffers.size());
    std::vector<VkVertexInputAttributeDescription> vertexAttributes;

    uint32_t currentBinding = 0;
    for (auto const& buffer : vertexInputState.buffers) {
        VkVertexInputBindingDescription vertexBindingDescription{};
        vertexBindingDescription.binding = currentBinding;
        vertexBindingDescription.stride = buffer.stride;

        switch (buffer.stepFunction) {
            case gfxtk::VertexStepFunction::PerVertex:
                vertexBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
                break;
            case gfxtk::VertexStepFunction::PerInstance:
                vertexBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
                break;
        }

        vertexBindingDescriptions.push_back(vertexBindingDescription);

        for (auto const& attribute : buffer.attributes) {
            VkVertexInputAttributeDescription vertexAttribute{};
            vertexAttribute.binding = currentBinding;
            vertexAttribute.offset = attribute.offset;
            vertexAttribute.location = attribute.location;
            vertexAttribute.format = gfxtk::backend::VertexFormat::convertToVkFormat(attribute.format);
            vertexAttributes.push_back(vertexAttribute);
        }

        ++currentBinding;
    }

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttributes.size());
    vertexInputInfo.pVertexAttributeDescriptions = vertexAttributes.data();
    vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindingDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = vertexBindingDescriptions.data();

    std::vector<VkViewport> vulkanViewports;
    std::vector<VkRect2D> vulkanScissors;
    vulkanViewports.reserve(viewportState.viewports.size());
    vulkanScissors.reserve(viewportState.scissors.size());

    for (auto const& viewport : viewportState.viewports) {
        VkViewport vulkanViewport{};
        vulkanViewport.x = viewport.x;
        vulkanViewport.y = viewport.y;
        vulkanViewport.width = viewport.width;
        vulkanViewport.height = viewport.height;
        vulkanViewport.minDepth = viewport.minDepth;
        vulkanViewport.maxDepth = viewport.maxDepth;
        vulkanViewports.push_back(vulkanViewport);
    }

    for (auto const& scissor : viewportState.scissors) {
        VkRect2D vulkanScissor{};
        vulkanScissor.offset.x = scissor.offset.x;
        vulkanScissor.offset.y = scissor.offset.y;
        vulkanScissor.extent.width = scissor.extent.width;
        vulkanScissor.extent.height = scissor.extent.height;
        vulkanScissors.push_back(vulkanScissor);
    }

    VkPipelineViewportStateCreateInfo vulkanViewportState{};
    vulkanViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vulkanViewportState.viewportCount = static_cast<uint32_t>(vulkanViewports.size());
    vulkanViewportState.scissorCount = static_cast<uint32_t>(vulkanScissors.size());
    vulkanViewportState.pViewports = vulkanViewports.data();
    vulkanViewportState.pScissors = vulkanScissors.data();

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = rasterizationState.depthClipMode == DepthClipMode::Clamp;
    rasterizer.polygonMode = backend::TriangleFillMode::convert(rasterizationState.fillMode);
    rasterizer.cullMode = backend::CullMode::convert(rasterizationState.cullMode);
    switch (rasterizationState.frontFace) {
        case Winding::Clockwise:
            rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
            break;
        case Winding::CounterClockwise:
            rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
            break;
    }
    rasterizer.depthBiasEnable = rasterizationState.depthBiasState.has_value();
    if (rasterizationState.depthBiasState.has_value()) {
        rasterizer.depthBiasConstantFactor = rasterizationState.depthBiasState->constantFactor;
        rasterizer.depthBiasClamp = rasterizationState.depthBiasState->clamp;
        rasterizer.depthBiasSlopeFactor = rasterizationState.depthBiasState->slopeScale;
    }
    rasterizer.lineWidth = 1.0f;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    if (multisampleState.has_value()) {
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.rasterizationSamples = backend::SampleCount::convert(multisampleState->rasterSampleCount);
        multisampling.alphaToCoverageEnable = multisampleState->isAlphaToCoverageEnabled;
        multisampling.alphaToOneEnable = multisampleState->isAlphaToOneEnabled;
    } else {
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    }

    std::vector<VkPipelineColorBlendAttachmentState> vulkanColorBlendAttachments;
    vulkanColorBlendAttachments.reserve(colorBlendAttachments.size());

    for (auto const& colorBlendAttachment : colorBlendAttachments) {
        VkPipelineColorBlendAttachmentState vulkanColorBlendAttachment{};
        vulkanColorBlendAttachment.blendEnable = colorBlendAttachment.isBlendingEnabled;
        vulkanColorBlendAttachment.colorWriteMask =
                backend::ColorWriteMask::convert(colorBlendAttachment.colorWriteMask);

        if (colorBlendAttachment.isBlendingEnabled) {
            vulkanColorBlendAttachment.srcColorBlendFactor =
                    backend::BlendFactor::convert(colorBlendAttachment.sourceColorBlendFactor);
            vulkanColorBlendAttachment.dstColorBlendFactor =
                    backend::BlendFactor::convert(colorBlendAttachment.destinationColorBlendFactor);
            vulkanColorBlendAttachment.colorBlendOp = backend::BlendOp::convert(colorBlendAttachment.colorBlendOp);
            vulkanColorBlendAttachment.srcAlphaBlendFactor =
                    backend::BlendFactor::convert(colorBlendAttachment.sourceAlphaBlendFactor);
            vulkanColorBlendAttachment.dstAlphaBlendFactor =
                    backend::BlendFactor::convert(colorBlendAttachment.destinationAlphaBlendFactor);
            vulkanColorBlendAttachment.alphaBlendOp = backend::BlendOp::convert(colorBlendAttachment.alphaBlendOp);
        }

        vulkanColorBlendAttachments.push_back(vulkanColorBlendAttachment);
    }

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.attachmentCount = static_cast<uint32_t>(vulkanColorBlendAttachments.size());
    colorBlending.pAttachments = vulkanColorBlendAttachments.data();
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    if (depthStencilState.has_value()) {
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthWriteEnable = depthStencilState->isDepthWriteEnabled;
        depthStencil.depthCompareOp = backend::CompareOp::convert(depthStencilState->depthCompareOp);
        depthStencil.front.failOp = backend::StencilOp::convert(depthStencilState->frontFaceStencil.stencilFailOp);
        depthStencil.front.depthFailOp = backend::StencilOp::convert(depthStencilState->frontFaceStencil.depthFailOp);
        depthStencil.front.passOp = backend::StencilOp::convert(depthStencilState->frontFaceStencil.depthStencilPassOp);
        depthStencil.front.compareOp = backend::CompareOp::convert(depthStencilState->frontFaceStencil.stencilCompareOp);
        depthStencil.front.compareMask = depthStencilState->frontFaceStencil.readMask;
        depthStencil.front.writeMask = depthStencilState->frontFaceStencil.writeMask;
        depthStencil.front.reference = depthStencilState->frontFaceStencil.reference;
        depthStencil.back.failOp = backend::StencilOp::convert(depthStencilState->backFaceStencil.stencilFailOp);
        depthStencil.back.depthFailOp = backend::StencilOp::convert(depthStencilState->backFaceStencil.depthFailOp);
        depthStencil.back.passOp = backend::StencilOp::convert(depthStencilState->backFaceStencil.depthStencilPassOp);
        depthStencil.back.compareOp = backend::CompareOp::convert(depthStencilState->backFaceStencil.stencilCompareOp);
        depthStencil.back.compareMask = depthStencilState->backFaceStencil.readMask;
        depthStencil.back.writeMask = depthStencilState->backFaceStencil.writeMask;
        depthStencil.back.reference = depthStencilState->backFaceStencil.reference;
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = static_cast<uint32_t>(vulkanShaderStages.size());
    pipelineInfo.pStages = vulkanShaderStages.data();
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &vulkanViewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    if (depthStencilState.has_value()) {
        pipelineInfo.pDepthStencilState = &depthStencil;
    }
    pipelineInfo.layout = pipelineLayout->vulkanPipelineLayout;
    pipelineInfo.renderPass = renderPassAttachment->vulkanRenderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    VkPipeline graphicsPipeline;

    if (vkCreateGraphicsPipelines(
            device->logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create Pipeline for Vulkan backend!");
    }

    return std::make_shared<Pipeline>(device->logicalDevice, graphicsPipeline);
}
