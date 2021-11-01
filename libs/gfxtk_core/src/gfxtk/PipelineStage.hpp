#ifndef GFXTK_PIPELINESTAGE_HPP
#define GFXTK_PIPELINESTAGE_HPP

#include "make_flags.hpp"

namespace gfxtk {
    enum class PipelineStage {
        Unknown = 0,
        BottomOfPipe = 0x0001,
        TopOfPipe = 0x0002,
        ColorAttachment = 0x0004,
        VertexShader = 0x0008,
        FragmentShader = 0x0010,
    };

    GFXTK_MAKE_ENUM_CLASS_FLAG(PipelineStage);
}

#endif //GFXTK_PIPELINESTAGE_HPP
