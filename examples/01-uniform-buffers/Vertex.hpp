#ifndef GFXTK_VERTEX_HPP
#define GFXTK_VERTEX_HPP

#include <glm/glm.hpp>
#include <gfxtk/VertexBufferLayout.hpp>

namespace gfxtk {
    struct Vertex {
        glm::vec2 position;
        glm::vec3 color;

        Vertex(float x, float y, float r, float g, float b)
                : position(x, y), color(r, g, b) {}
        Vertex(glm::vec2 position, glm::vec3 color)
                : position(position), color(color) {}

        static VertexBufferLayout getVertexBufferLayout() {
            return VertexBufferLayout(
                    sizeof(Vertex),
                    VertexStepFunction::PerVertex,
                    {
                        VertexAttribute(0, VertexFormat::Float2, offsetof(Vertex, position)),
                        VertexAttribute(1, VertexFormat::Float3, offsetof(Vertex, color))
                    }
            );
        }

    };
}

#endif //GFXTK_VERTEX_HPP
