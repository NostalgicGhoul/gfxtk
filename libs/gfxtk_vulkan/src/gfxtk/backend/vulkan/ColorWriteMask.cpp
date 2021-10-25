#include "ColorWriteMask.hpp"

VkColorComponentFlags gfxtk::backend::ColorWriteMask::convert(gfxtk::ColorWriteMask colorWriteMask) {
    VkColorComponentFlags result{};

    if ((colorWriteMask & gfxtk::ColorWriteMask::R) == gfxtk::ColorWriteMask::R) {
        result |= VK_COLOR_COMPONENT_R_BIT;
    }

    if ((colorWriteMask & gfxtk::ColorWriteMask::G) == gfxtk::ColorWriteMask::G) {
        result |= VK_COLOR_COMPONENT_G_BIT;
    }

    if ((colorWriteMask & gfxtk::ColorWriteMask::B) == gfxtk::ColorWriteMask::B) {
        result |= VK_COLOR_COMPONENT_B_BIT;
    }

    if ((colorWriteMask & gfxtk::ColorWriteMask::A) == gfxtk::ColorWriteMask::A) {
        result |= VK_COLOR_COMPONENT_A_BIT;
    }

    return result;
}
