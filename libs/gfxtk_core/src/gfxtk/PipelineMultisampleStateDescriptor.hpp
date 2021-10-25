#ifndef GFXTK_PIPELINEMULTISAMPLESTATEDESCRIPTOR_HPP
#define GFXTK_PIPELINEMULTISAMPLESTATEDESCRIPTOR_HPP

#include "SampleCount.hpp"

namespace gfxtk {
    struct PipelineMultisampleStateDescriptor {
        SampleCount rasterSampleCount;
        bool isAlphaToCoverageEnabled;
        bool isAlphaToOneEnabled;

        PipelineMultisampleStateDescriptor(
                SampleCount rasterSampleCount,
                bool isAlphaToCoverageEnabled,
                bool isAlphaToOneEnabled
        ) : rasterSampleCount(rasterSampleCount),
            isAlphaToCoverageEnabled(isAlphaToCoverageEnabled),
            isAlphaToOneEnabled(isAlphaToOneEnabled) {}

    };
}

#endif //GFXTK_PIPELINEMULTISAMPLESTATEDESCRIPTOR_HPP
