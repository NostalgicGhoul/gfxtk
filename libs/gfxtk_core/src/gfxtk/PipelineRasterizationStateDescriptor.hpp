#ifndef GFXTK_PIPELINERASTERIZATIONSTATEDESCRIPTOR_HPP
#define GFXTK_PIPELINERASTERIZATIONSTATEDESCRIPTOR_HPP

#include "microsoft_fix.hpp"
#include <optional>
#include "DepthClipMode.hpp"
#include "TriangleFillMode.hpp"
#include "CullMode.hpp"
#include "Winding.hpp"
#include "PipelineDepthBiasStateDescriptor.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT PipelineRasterizationStateDescriptor {
        DepthClipMode depthClipMode;
        // TODO: My assumption is Vulkan's `rasterizerDiscardEnable` is the inverse of Metal's `isRasterizationEnabled`
        //       but because I'm not 100% sure (and I really can't think of a reason for this to exist at the moment)
        //       I've decided to skip this feature for now.
        TriangleFillMode fillMode;
        CullMode cullMode;
        Winding frontFace;
        std::optional<PipelineDepthBiasStateDescriptor> depthBiasState;

        PipelineRasterizationStateDescriptor(
                DepthClipMode depthClipMode,
                TriangleFillMode fillMode,
                CullMode cullMode,
                Winding frontFace,
                std::optional<PipelineDepthBiasStateDescriptor> depthBiasState = std::nullopt
        ) : depthClipMode(depthClipMode),
            fillMode(fillMode),
            cullMode(cullMode),
            frontFace(frontFace),
            depthBiasState(depthBiasState) {}

    };
}

#endif //GFXTK_PIPELINERASTERIZATIONSTATEDESCRIPTOR_HPP
