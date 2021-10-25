#ifndef GFXTK_BACKEND_VULKAN_PIPELINE_HPP
#define GFXTK_BACKEND_VULKAN_PIPELINE_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <optional>
#include <gfxtk/PipelineVertexInputStateDescriptor.hpp>
#include <gfxtk/PrimitiveTopology.hpp>
#include <gfxtk/PipelineViewportStateDescriptor.hpp>
#include <gfxtk/PipelineRasterizationStateDescriptor.hpp>
#include <gfxtk/PipelineMultisampleStateDescriptor.hpp>
#include <gfxtk/PipelineDepthStencilStateDescriptor.hpp>
#include <gfxtk/PipelineColorBlendAttachmentDescriptor.hpp>
#include "Device.hpp"
#include "Shader.hpp"
#include "PipelineLayout.hpp"
#include "RenderPassAttachment.hpp"

namespace gfxtk::backend {
    struct Pipeline {
        static std::shared_ptr<Pipeline> createRenderPipeline(
                std::shared_ptr<backend::Device> const& device,
                std::shared_ptr<backend::Shader> const& vertexShader,
                std::shared_ptr<backend::Shader> const& fragmentShader,
                PipelineVertexInputStateDescriptor const& vertexInputState,
                PrimitiveTopology primitiveTopology,
                PipelineViewportStateDescriptor const& viewportState,
                PipelineRasterizationStateDescriptor const& rasterizationState,
                std::optional<PipelineMultisampleStateDescriptor> const& multisampleState,
                std::optional<PipelineDepthStencilStateDescriptor> const& depthStencilState,
                std::vector<PipelineColorBlendAttachmentDescriptor> const& colorBlendAttachments,
                std::shared_ptr<backend::PipelineLayout> const& pipelineLayout,
                std::shared_ptr<backend::RenderPassAttachment> const& renderPassAttachment
        );

        VkDevice vulkanDevice;
        VkPipeline vulkanPipeline;

        Pipeline(VkDevice vulkanDevice, VkPipeline vulkanPipeline)
                : vulkanDevice(vulkanDevice), vulkanPipeline(vulkanPipeline) {}
        ~Pipeline() {
            vkDestroyPipeline(vulkanDevice, vulkanPipeline, nullptr);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_PIPELINE_HPP
