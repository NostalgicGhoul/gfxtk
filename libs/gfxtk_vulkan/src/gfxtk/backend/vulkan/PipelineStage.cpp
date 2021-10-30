#include <gfxtk/log.hpp>
#include "PipelineStage.hpp"

VkPipelineStageFlags gfxtk::backend::PipelineStage::convert(gfxtk::PipelineStage pipelineStage) {
    switch (pipelineStage) {
        case gfxtk::PipelineStage::BottomOfPipe:
            return VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        case gfxtk::PipelineStage::TopOfPipe:
            return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        case gfxtk::PipelineStage::ColorAttachment:
            return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        default:
            GFXTK_LOG_F("unknown `PipelineStage` passed to `gfxtk::backend::PipelineStage::convert`!");
    }
}
