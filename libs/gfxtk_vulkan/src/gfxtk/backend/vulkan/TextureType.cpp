#include "TextureType.hpp"

VkImageType gfxtk::backend::TextureType::convert(gfxtk::TextureType textureType) {
    switch (textureType) {
        case gfxtk::TextureType::Type1D:
            return VK_IMAGE_TYPE_1D;
        case gfxtk::TextureType::Type2D:
            return VK_IMAGE_TYPE_2D;
        case gfxtk::TextureType::Type3D:
            return VK_IMAGE_TYPE_3D;
    }
}
