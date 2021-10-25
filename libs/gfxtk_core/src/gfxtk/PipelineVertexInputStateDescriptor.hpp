#ifndef GFXTK_PIPELINEVERTEXINPUTSTATEDESCRIPTOR_HPP
#define GFXTK_PIPELINEVERTEXINPUTSTATEDESCRIPTOR_HPP

#include <vector>
#include "VertexBufferLayout.hpp"

namespace gfxtk {
    struct PipelineVertexInputStateDescriptor {
        std::vector<VertexBufferLayout> buffers;

        explicit PipelineVertexInputStateDescriptor(std::vector<VertexBufferLayout> buffers)
                : buffers(std::move(buffers)) {}

    };
}

#endif //GFXTK_PIPELINEVERTEXINPUTSTATEDESCRIPTOR_HPP
