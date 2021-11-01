#ifndef GFXTK_VERTEX_HPP
#define GFXTK_VERTEX_HPP

#include <glm/glm.hpp>
#include <gfxtk/VertexBufferLayout.hpp>

namespace gfxtk {
    struct Vertex {
        glm::vec2 position;
        glm::vec3 color;
        glm::vec2 texCoord;

        Vertex(float x, float y, float r, float g, float b, float u, float v)
                : position(x, y), color(r, g, b), texCoord(u, v) {}
        Vertex(glm::vec2 position, glm::vec3 color, glm::vec2 texCoord)
                : position(position), color(color), texCoord(texCoord) {}

        static VertexBufferLayout getVertexBufferLayout() {
            return VertexBufferLayout(
                    sizeof(Vertex),
                    VertexStepFunction::PerVertex,
                    {
                        VertexAttribute(0, VertexFormat::Float2, offsetof(Vertex, position)),
                        VertexAttribute(1, VertexFormat::Float3, offsetof(Vertex, color)),
                        VertexAttribute(2, VertexFormat::Float2, offsetof(Vertex, texCoord))
                    }
            );
        }

    };
}

#endif //GFXTK_VERTEX_HPP
