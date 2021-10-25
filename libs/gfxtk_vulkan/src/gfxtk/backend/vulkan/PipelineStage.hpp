#ifndef GFXTK_BACKEND_VULKAN_PIPELINESTAGE_HPP
#define GFXTK_BACKEND_VULKAN_PIPELINESTAGE_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/PipelineStage.hpp>

namespace gfxtk::backend {
    struct PipelineStage {
        static VkPipelineStageFlags convert(gfxtk::PipelineStage pipelineStage);

    };
}

#endif //GFXTK_BACKEND_VULKAN_PIPELINESTAGE_HPP
