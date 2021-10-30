#include <gfxtk/log.hpp>
#include "CullMode.hpp"

VkCullModeFlags gfxtk::backend::CullMode::convert(gfxtk::CullMode cullMode) {
    switch (cullMode) {
        case gfxtk::CullMode::None:
            return VK_CULL_MODE_NONE;
        case gfxtk::CullMode::Back:
            return VK_CULL_MODE_BACK_BIT;
        case gfxtk::CullMode::Front:
            return VK_CULL_MODE_FRONT_BIT;
        default:
            GFXTK_LOG_F("unknown `CullMode` passed to `gfxtk::backend::CullMode::convert`!");
    }
}
