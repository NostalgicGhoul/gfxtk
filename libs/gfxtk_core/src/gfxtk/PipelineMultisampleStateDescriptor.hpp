#ifndef GFXTK_PIPELINEMULTISAMPLESTATEDESCRIPTOR_HPP
#define GFXTK_PIPELINEMULTISAMPLESTATEDESCRIPTOR_HPP

#include "microsoft_fix.hpp"
#include "SampleCount.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT PipelineMultisampleStateDescriptor {
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
