#include <gfxtk/log.hpp>
#include "PixelFormat.hpp"

VkFormat gfxtk::backend::PixelFormat::convertToVkFormat(gfxtk::PixelFormat pixelFormat) {
    switch (pixelFormat) {
        case gfxtk::PixelFormat::Invalid: return VK_FORMAT_UNDEFINED;
        case gfxtk::PixelFormat::R8Unorm: return VK_FORMAT_R8_UNORM;
        case gfxtk::PixelFormat::R8Unorm_srgb: return VK_FORMAT_R8_SRGB;
        case gfxtk::PixelFormat::R8Snorm: return VK_FORMAT_R8_SNORM;
        case gfxtk::PixelFormat::R8Uint: return VK_FORMAT_R8_UINT;
        case gfxtk::PixelFormat::R8Sint: return VK_FORMAT_R8_SINT;
        case gfxtk::PixelFormat::R16Unorm: return VK_FORMAT_R16_UNORM;
        case gfxtk::PixelFormat::R16Snorm: return VK_FORMAT_R16_SNORM;
        case gfxtk::PixelFormat::R16Uint: return VK_FORMAT_R16_UINT;
        case gfxtk::PixelFormat::R16Sint: return VK_FORMAT_R16_SINT;
        case gfxtk::PixelFormat::R16Float: return VK_FORMAT_R16_SFLOAT;
        case gfxtk::PixelFormat::RG8Unorm: return VK_FORMAT_R8G8_UNORM;
        case gfxtk::PixelFormat::RG8Unorm_srgb: return VK_FORMAT_R8G8_SRGB;
        case gfxtk::PixelFormat::RG8Snorm: return VK_FORMAT_R8G8_SNORM;
        case gfxtk::PixelFormat::RG8Uint: return VK_FORMAT_R8G8_UINT;
        case gfxtk::PixelFormat::RG8Sint: return VK_FORMAT_R8G8_SINT;
        case gfxtk::PixelFormat::B5G6R5Unorm: return VK_FORMAT_B5G6R5_UNORM_PACK16;
        case gfxtk::PixelFormat::BGR5A1Unorm: return VK_FORMAT_B5G5R5A1_UNORM_PACK16;
        case gfxtk::PixelFormat::R32Uint: return VK_FORMAT_R32_UINT;
        case gfxtk::PixelFormat::R32Sint: return VK_FORMAT_R32_SINT;
        case gfxtk::PixelFormat::R32Float: return VK_FORMAT_R32_SFLOAT;
        case gfxtk::PixelFormat::RG16Unorm: return VK_FORMAT_R16G16_UNORM;
        case gfxtk::PixelFormat::RG16Snorm: return VK_FORMAT_R16G16_SNORM;
        case gfxtk::PixelFormat::RG16Uint: return VK_FORMAT_R16G16_UINT;
        case gfxtk::PixelFormat::RG16Sint: return VK_FORMAT_R16G16_SINT;
        case gfxtk::PixelFormat::RG16Float: return VK_FORMAT_R16G16_SFLOAT;
        case gfxtk::PixelFormat::RGBA8Unorm: return VK_FORMAT_R8G8B8A8_UNORM;
        case gfxtk::PixelFormat::RGBA8Unorm_srgb: return VK_FORMAT_R8G8B8A8_SRGB;
        case gfxtk::PixelFormat::RGBA8Snorm: return VK_FORMAT_R8G8B8A8_SNORM;
        case gfxtk::PixelFormat::RGBA8Uint: return VK_FORMAT_R8G8B8A8_UINT;
        case gfxtk::PixelFormat::RGBA8Sint: return VK_FORMAT_R8G8B8A8_SINT;
        case gfxtk::PixelFormat::BGRA8Unorm: return VK_FORMAT_B8G8R8A8_UNORM;
        case gfxtk::PixelFormat::BGRA8Unorm_srgb: return VK_FORMAT_B8G8R8A8_SRGB;
        case gfxtk::PixelFormat::RG32Uint: return VK_FORMAT_R32G32_UINT;
        case gfxtk::PixelFormat::RG32Float: return VK_FORMAT_R32G32_SFLOAT;
        case gfxtk::PixelFormat::RGBA16Unorm: return VK_FORMAT_R16G16B16A16_UNORM;
        case gfxtk::PixelFormat::RGBA16Snorm: return VK_FORMAT_R16G16B16A16_SNORM;
        case gfxtk::PixelFormat::RGBA16Uint: return VK_FORMAT_R16G16B16A16_UINT;
        case gfxtk::PixelFormat::RGBA16Sint: return VK_FORMAT_R16G16B16A16_SINT;
        case gfxtk::PixelFormat::RGBA16Float: return VK_FORMAT_R16G16B16_SFLOAT;
        case gfxtk::PixelFormat::RGBA32Uint: return VK_FORMAT_R32G32B32A32_UINT;
        case gfxtk::PixelFormat::RGBA32Sint: return VK_FORMAT_R32G32B32A32_SINT;
        case gfxtk::PixelFormat::RGBA32Float: return VK_FORMAT_R32G32B32A32_SFLOAT;
        case gfxtk::PixelFormat::PVRTC1_rgba_2bpp: return VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG;
        case gfxtk::PixelFormat::PVRTC1_rgba_2bpp_srgb: return VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG;
        case gfxtk::PixelFormat::PVRTC1_rgba_4bpp: return VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG;
        case gfxtk::PixelFormat::PVRTC1_rgba_4bpp_srgb: return VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG;
        case gfxtk::PixelFormat::ASTC_4x4_srgb: return VK_FORMAT_ASTC_4x4_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_5x4_srgb: return VK_FORMAT_ASTC_5x4_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_5x5_srgb: return VK_FORMAT_ASTC_5x5_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_6x5_srgb: return VK_FORMAT_ASTC_6x5_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_6x6_srgb: return VK_FORMAT_ASTC_6x6_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_8x5_srgb: return VK_FORMAT_ASTC_8x5_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_8x6_srgb: return VK_FORMAT_ASTC_8x6_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_8x8_srgb: return VK_FORMAT_ASTC_8x8_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_10x5_srgb: return VK_FORMAT_ASTC_10x5_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_10x6_srgb: return VK_FORMAT_ASTC_10x6_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_10x8_srgb: return VK_FORMAT_ASTC_10x8_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_10x10_srgb: return VK_FORMAT_ASTC_10x10_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_12x10_srgb: return VK_FORMAT_ASTC_12x10_SRGB_BLOCK;
        case gfxtk::PixelFormat::ASTC_12x12_srgb: return VK_FORMAT_ASTC_12x12_SRGB_BLOCK;
        case gfxtk::PixelFormat::BC1_rgba: return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case gfxtk::PixelFormat::BC1_rgba_srgb: return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
        case gfxtk::PixelFormat::BC2_rgba: return VK_FORMAT_BC2_UNORM_BLOCK;
        case gfxtk::PixelFormat::BC2_rgba_srgb: return VK_FORMAT_BC2_SRGB_BLOCK;
        case gfxtk::PixelFormat::BC3_rgba: return VK_FORMAT_BC3_UNORM_BLOCK;
        case gfxtk::PixelFormat::BC3_rgba_srgb: return VK_FORMAT_BC3_SRGB_BLOCK;
        case gfxtk::PixelFormat::BC4_rUnorm: return VK_FORMAT_BC4_UNORM_BLOCK;
        case gfxtk::PixelFormat::BC4_rSnorm: return VK_FORMAT_BC4_SNORM_BLOCK;
        case gfxtk::PixelFormat::BC5_rgUnorm: return VK_FORMAT_BC5_UNORM_BLOCK;
        case gfxtk::PixelFormat::BC5_rgSnorm: return VK_FORMAT_BC5_SNORM_BLOCK;
        case gfxtk::PixelFormat::BC6H_rgbFloat: return VK_FORMAT_BC6H_SFLOAT_BLOCK;
        case gfxtk::PixelFormat::BC6H_rgbuFloat: return VK_FORMAT_BC6H_UFLOAT_BLOCK;
        case gfxtk::PixelFormat::BC7_rgbaUnorm: return VK_FORMAT_BC7_UNORM_BLOCK;
        case gfxtk::PixelFormat::BC7_rgbaUnorm_srgb: return VK_FORMAT_BC7_SRGB_BLOCK;
        case gfxtk::PixelFormat::Depth16Unorm: return VK_FORMAT_D16_UNORM;
        case gfxtk::PixelFormat::Depth32Float: return VK_FORMAT_D32_SFLOAT;
        case gfxtk::PixelFormat::Stencil8: return VK_FORMAT_S8_UINT;
        case gfxtk::PixelFormat::Depth24Unorm_stencil8: return VK_FORMAT_D24_UNORM_S8_UINT;
        case gfxtk::PixelFormat::Depth32Float_stencil8: return VK_FORMAT_D32_SFLOAT_S8_UINT;
        default:
            GFXTK_LOG_F("unknown PixelFormat provided!");
            return VK_FORMAT_UNDEFINED;
    }
}
