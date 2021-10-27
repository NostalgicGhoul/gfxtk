#include "VertexFormat.hpp"

VkFormat gfxtk::backend::VertexFormat::convertToVkFormat(gfxtk::VertexFormat vertexFormat) {
    switch (vertexFormat) {
        case gfxtk::VertexFormat::Invalid:
            return VK_FORMAT_UNDEFINED;
        case gfxtk::VertexFormat::Uchar:
            return VK_FORMAT_R8_UINT;
        case gfxtk::VertexFormat::Uchar2:
            return VK_FORMAT_R8G8_UINT;
        case gfxtk::VertexFormat::Uchar3:
            return VK_FORMAT_R8G8B8_UINT;
        case gfxtk::VertexFormat::Uchar4:
            return VK_FORMAT_R8G8B8A8_UINT;
        case gfxtk::VertexFormat::Char:
            return VK_FORMAT_R8_SINT;
        case gfxtk::VertexFormat::Char2:
            return VK_FORMAT_R8G8_SINT;
        case gfxtk::VertexFormat::Char3:
            return VK_FORMAT_R8G8B8_SINT;
        case gfxtk::VertexFormat::Char4:
            return VK_FORMAT_R8G8B8A8_SINT;
        case gfxtk::VertexFormat::UcharNorm:
            return VK_FORMAT_R8_UNORM;
        case gfxtk::VertexFormat::Uchar2Norm:
            return VK_FORMAT_R8G8_UNORM;
        case gfxtk::VertexFormat::Uchar3Norm:
            return VK_FORMAT_R8G8B8_UNORM;
        case gfxtk::VertexFormat::Uchar4Norm:
            return VK_FORMAT_R8G8B8A8_UNORM;
        case gfxtk::VertexFormat::CharNorm:
            return VK_FORMAT_R8_SNORM;
        case gfxtk::VertexFormat::Char2Norm:
            return VK_FORMAT_R8G8_SNORM;
        case gfxtk::VertexFormat::Char3Norm:
            return VK_FORMAT_R8G8B8_SNORM;
        case gfxtk::VertexFormat::Char4Norm:
            return VK_FORMAT_R8G8B8A8_SNORM;
        case gfxtk::VertexFormat::Ushort:
            return VK_FORMAT_R16_UINT;
        case gfxtk::VertexFormat::Ushort2:
            return VK_FORMAT_R16G16_UINT;
        case gfxtk::VertexFormat::Ushort3:
            return VK_FORMAT_R16G16B16_UINT;
        case gfxtk::VertexFormat::Ushort4:
            return VK_FORMAT_R16G16B16A16_UINT;
        case gfxtk::VertexFormat::Short:
            return VK_FORMAT_R16_SINT;
        case gfxtk::VertexFormat::Short2:
            return VK_FORMAT_R16G16_SINT;
        case gfxtk::VertexFormat::Short3:
            return VK_FORMAT_R16G16B16_SINT;
        case gfxtk::VertexFormat::Short4:
            return VK_FORMAT_R16G16B16A16_SINT;
        case gfxtk::VertexFormat::UshortNorm:
            return VK_FORMAT_R16_UNORM;
        case gfxtk::VertexFormat::Ushort2Norm:
            return VK_FORMAT_R16G16_UNORM;
        case gfxtk::VertexFormat::Ushort3Norm:
            return VK_FORMAT_R16G16B16_UNORM;
        case gfxtk::VertexFormat::Ushort4Norm:
            return VK_FORMAT_R16G16B16A16_UNORM;
        case gfxtk::VertexFormat::ShortNorm:
            return VK_FORMAT_R16_SNORM;
        case gfxtk::VertexFormat::Short2Norm:
            return VK_FORMAT_R16G16_SNORM;
        case gfxtk::VertexFormat::Short3Norm:
            return VK_FORMAT_R16G16B16_SNORM;
        case gfxtk::VertexFormat::Short4Norm:
            return VK_FORMAT_R16G16B16A16_SNORM;
        case gfxtk::VertexFormat::Half:
            return VK_FORMAT_R16_SFLOAT;
        case gfxtk::VertexFormat::Half2:
            return VK_FORMAT_R16G16_SFLOAT;
        case gfxtk::VertexFormat::Half3:
            return VK_FORMAT_R16G16B16_SFLOAT;
        case gfxtk::VertexFormat::Half4:
            return VK_FORMAT_R16G16B16A16_SFLOAT;
        case gfxtk::VertexFormat::Float:
            return VK_FORMAT_R32_SFLOAT;
        case gfxtk::VertexFormat::Float2:
            return VK_FORMAT_R32G32_SFLOAT;
        case gfxtk::VertexFormat::Float3:
            return VK_FORMAT_R32G32B32_SFLOAT;
        case gfxtk::VertexFormat::Float4:
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case gfxtk::VertexFormat::Uint:
            return VK_FORMAT_R32_UINT;
        case gfxtk::VertexFormat::Uint2:
            return VK_FORMAT_R32G32_UINT;
        case gfxtk::VertexFormat::Uint3:
            return VK_FORMAT_R32G32B32_UINT;
        case gfxtk::VertexFormat::Uint4:
            return VK_FORMAT_R32G32B32A32_UINT;
        case gfxtk::VertexFormat::Int:
            return VK_FORMAT_R32_SINT;
        case gfxtk::VertexFormat::Int2:
            return VK_FORMAT_R32G32_SINT;
        case gfxtk::VertexFormat::Int3:
            return VK_FORMAT_R32G32B32_SINT;
        case gfxtk::VertexFormat::Int4:
            return VK_FORMAT_R32G32B32A32_SINT;
    }
}