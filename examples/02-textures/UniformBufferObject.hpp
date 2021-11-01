#ifndef GFXTK_UNIFORMBUFFEROBJECT_HPP
#define GFXTK_UNIFORMBUFFEROBJECT_HPP

#include <glm/glm.hpp>

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

#endif //GFXTK_UNIFORMBUFFEROBJECT_HPP
