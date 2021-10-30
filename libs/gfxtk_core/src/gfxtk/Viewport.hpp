#ifndef GFXTK_VIEWPORT_HPP
#define GFXTK_VIEWPORT_HPP

#include "microsoft_fix.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT Viewport {
        float x;
        float y;
        float width;
        float height;
        float minDepth;
        float maxDepth;

        Viewport() = default;
        Viewport(float x, float y, float width, float height, float minDepth, float maxDepth)
                : x(x), y(y), width(width), height(height), minDepth(minDepth), maxDepth(maxDepth) {}

    };
}

#endif //GFXTK_VIEWPORT_HPP
