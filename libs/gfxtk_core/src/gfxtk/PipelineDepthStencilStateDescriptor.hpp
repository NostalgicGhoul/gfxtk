#ifndef GFXTK_PIPELINEDEPTHSTENCILSTATEDESCRIPTOR_HPP
#define GFXTK_PIPELINEDEPTHSTENCILSTATEDESCRIPTOR_HPP

#include "microsoft_fix.hpp"
#include "CompareOp.hpp"
#include "StencilDescriptor.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT PipelineDepthStencilStateDescriptor {
        bool isDepthWriteEnabled;
        CompareOp depthCompareOp;
        StencilDescriptor frontFaceStencil;
        StencilDescriptor backFaceStencil;

        PipelineDepthStencilStateDescriptor(
                bool isDepthWriteEnabled,
                CompareOp depthCompareOp,
                StencilDescriptor frontFaceStencil,
                StencilDescriptor backFaceStencil
        ) : isDepthWriteEnabled(isDepthWriteEnabled),
            depthCompareOp(depthCompareOp),
            frontFaceStencil(frontFaceStencil),
            backFaceStencil(backFaceStencil) {}

    };
}

#endif //GFXTK_PIPELINEDEPTHSTENCILSTATEDESCRIPTOR_HPP
