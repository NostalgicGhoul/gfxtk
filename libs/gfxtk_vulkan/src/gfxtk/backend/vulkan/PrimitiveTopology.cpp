#include <gfxtk/log.hpp>
#include "PrimitiveTopology.hpp"

VkPrimitiveTopology gfxtk::backend::PrimitiveTopology::convertToVkPrimitiveTopology(
        gfxtk::PrimitiveTopology primitiveTopology
) {
    switch (primitiveTopology) {
        case gfxtk::PrimitiveTopology::Line:
            return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
        case gfxtk::PrimitiveTopology::Point:
            return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
        case gfxtk::PrimitiveTopology::Triangle:
            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        default:
            GFXTK_LOG_F("unknown `PrimitiveTopology` passed to `gfxtk::backend::PrimitiveTopology::convertToVkPrimitiveTopology`!");
    }
}
