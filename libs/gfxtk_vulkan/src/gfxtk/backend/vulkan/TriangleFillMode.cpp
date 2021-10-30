#include <gfxtk/log.hpp>
#include "TriangleFillMode.hpp"

VkPolygonMode gfxtk::backend::TriangleFillMode::convert(gfxtk::TriangleFillMode fillMode) {
    switch (fillMode) {
        case gfxtk::TriangleFillMode::Lines:
            return VK_POLYGON_MODE_LINE;
        case gfxtk::TriangleFillMode::Fill:
            return VK_POLYGON_MODE_FILL;
        default:
            GFXTK_LOG_F("unknown `TriangleFillMode` found in `gfxtk::backend::TriangleFillMode::convert`!");
    }
}
