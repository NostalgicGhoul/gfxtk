#include <gfxtk/log.hpp>
#include "PipelineStage.hpp"

VkPipelineStageFlags gfxtk::backend::PipelineStage::convert(gfxtk::PipelineStage pipelineStage) {
    VkPipelineStageFlags result = 0;

    if ((pipelineStage & gfxtk::PipelineStage::BottomOfPipe) == gfxtk::PipelineStage::BottomOfPipe) {
        result |= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    }

    if ((pipelineStage & gfxtk::PipelineStage::TopOfPipe) == gfxtk::PipelineStage::TopOfPipe) {
        result |= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    }

    if ((pipelineStage & gfxtk::PipelineStage::ColorAttachment) == gfxtk::PipelineStage::ColorAttachment) {
        result |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }

    if ((pipelineStage & gfxtk::PipelineStage::VertexShader) == gfxtk::PipelineStage::VertexShader) {
        result |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
    }

    if ((pipelineStage & gfxtk::PipelineStage::FragmentShader) == gfxtk::PipelineStage::FragmentShader) {
        result |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }

    return result;
}
