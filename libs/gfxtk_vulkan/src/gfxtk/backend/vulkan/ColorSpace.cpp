#include <gfxtk/log.hpp>
#include "ColorSpace.hpp"

VkColorSpaceKHR gfxtk::backend::ColorSpace::convertToVkColorSpaceKHR(gfxtk::ColorSpace colorSpace) {
    switch (colorSpace) {
        case gfxtk::ColorSpace::SRGB: return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        // TODO: Is this right? Is it non-linear?
        case gfxtk::ColorSpace::DisplayP3: return VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT;
        case gfxtk::ColorSpace::ExtendedSRGB: return VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT;
        case gfxtk::ColorSpace::ExtendedLinearSRGB: return VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT;
        // TODO: Same question, is this right?
        case gfxtk::ColorSpace::DCIP3: return VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT;
        // TODO: Same question, is this right? Is this one linear?
        case gfxtk::ColorSpace::BT709: return VK_COLOR_SPACE_BT709_LINEAR_EXT;
        case gfxtk::ColorSpace::BT2020: return VK_COLOR_SPACE_BT2020_LINEAR_EXT;
        // TODO: Again, linear or non-linear?
        case gfxtk::ColorSpace::AdobeRGB1998: return VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT;
        case gfxtk::ColorSpace::Invalid:
        default:
            GFXTK_LOG_F("unknown ColorSpace provided!");
            return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    }
}
