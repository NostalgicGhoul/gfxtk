#include "TriangleFillMode.hpp"

VkPolygonMode gfxtk::backend::TriangleFillMode::convert(gfxtk::TriangleFillMode fillMode) {
    switch (fillMode) {
        case gfxtk::TriangleFillMode::Lines:
            return VK_POLYGON_MODE_LINE;
        case gfxtk::TriangleFillMode::Fill:
            return VK_POLYGON_MODE_FILL;
    }
}
