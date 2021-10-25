#ifndef GFXTK_VERTEXATTRIBUTE_HPP
#define GFXTK_VERTEXATTRIBUTE_HPP

#include <cstdint>
#include "VertexFormat.hpp"

namespace gfxtk {
    struct VertexAttribute {
        uint32_t location;
        VertexFormat format;
        uint32_t offset;

        VertexAttribute(uint32_t location, VertexFormat format, uint32_t offset)
                : location(location), format(format), offset(offset) {}

    };
}

#endif //GFXTK_VERTEXATTRIBUTE_HPP
