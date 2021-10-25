#ifndef GFXTK_PIPELINEDEPTHBIASSTATEDESCRIPTOR_HPP
#define GFXTK_PIPELINEDEPTHBIASSTATEDESCRIPTOR_HPP

namespace gfxtk {
    struct PipelineDepthBiasStateDescriptor {
        float constantFactor;
        float slopeScale;
        float clamp;

        PipelineDepthBiasStateDescriptor(float constantFactor, float slopeScale, float clamp)
                : constantFactor(constantFactor), slopeScale(slopeScale), clamp(clamp) {}

    };
}

#endif //GFXTK_PIPELINEDEPTHBIASSTATEDESCRIPTOR_HPP
