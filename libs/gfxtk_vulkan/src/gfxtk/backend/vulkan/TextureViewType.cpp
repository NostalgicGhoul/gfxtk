#include "TextureViewType.hpp"

VkImageViewType gfxtk::backend::TextureViewType::convert(gfxtk::TextureViewType textureViewType) {
    switch (textureViewType) {
        case gfxtk::TextureViewType::Type1D:
            return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
        case gfxtk::TextureViewType::Type2D:
            return VK_IMAGE_VIEW_TYPE_2D;
        case gfxtk::TextureViewType::Type3D:
            return VK_IMAGE_VIEW_TYPE_3D;
        case gfxtk::TextureViewType::TypeCube:
            return VK_IMAGE_VIEW_TYPE_CUBE;
        case gfxtk::TextureViewType::Type2DArray:
            return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
        case gfxtk::TextureViewType::TypeCubeArray:
            return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
    }
}
