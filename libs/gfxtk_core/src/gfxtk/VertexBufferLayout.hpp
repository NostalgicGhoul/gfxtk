#ifndef GFXTK_VERTEXBUFFERLAYOUT_HPP
#define GFXTK_VERTEXBUFFERLAYOUT_HPP

#include <cstdint>
#include <vector>
#include "VertexStepFunction.hpp"
#include "VertexAttribute.hpp"

namespace gfxtk {
    struct VertexBufferLayout {
        uint32_t stride;
        VertexStepFunction stepFunction;
        std::vector<VertexAttribute> attributes;

        VertexBufferLayout(uint32_t stride, VertexStepFunction stepFunction, std::vector<VertexAttribute> attributes)
                : stride(stride), stepFunction(stepFunction), attributes(std::move(attributes)) {}

    };
}

#endif //GFXTK_VERTEXBUFFERLAYOUT_HPP
