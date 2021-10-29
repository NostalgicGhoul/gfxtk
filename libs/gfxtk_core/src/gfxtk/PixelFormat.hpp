#ifndef GFXTK_PIXELFORMAT_HPP
#define GFXTK_PIXELFORMAT_HPP

namespace gfxtk {
    enum class PixelFormat {
        Invalid = 0,

        // Ordinary 8-bit formats
        R8Unorm,
        R8Unorm_srgb,
        R8Snorm,
        R8Uint,
        R8Sint,

        // Ordinary 16-bit formats
        R16Unorm,
        R16Snorm,
        R16Uint,
        R16Sint,
        R16Float,
        RG8Unorm,
        RG8Unorm_srgb,
        RG8Snorm,
        RG8Uint,
        RG8Sint,

        // Packed 16-bit formats
        B5G6R5Unorm,
        BGR5A1Unorm,

        // Ordinary 32-bit formats
        R32Uint,
        R32Sint,
        R32Float,
        RG16Unorm,
        RG16Snorm,
        RG16Uint,
        RG16Sint,
        RG16Float,
        RGBA8Unorm,
        RGBA8Unorm_srgb,
        RGBA8Snorm,
        RGBA8Uint,
        RGBA8Sint,
        BGRA8Unorm,
        BGRA8Unorm_srgb,

        // Packed 32-bit formats
        // NOTE: Vulkan and Metal do not share any packed 32-bit formats. Therefore, we don't support them at the moment

        // Ordinary 64-bit formats
        RG32Uint,
        RG32Sint,
        RG32Float,
        RGBA16Unorm,
        RGBA16Snorm,
        RGBA16Uint,
        RGBA16Sint,
        RGBA16Float,

        // Ordinary 128-bit formats
        RGBA32Uint,
        RGBA32Sint,
        RGBA32Float,

        // Compressed PVRTC1 formats
        PVRTC1_rgba_2bpp,
        PVRTC1_rgba_2bpp_srgb,
        PVRTC1_rgba_4bpp,
        PVRTC1_rgba_4bpp_srgb,

        // Compressed PVRTC2 formats
        // NOTE: Metal does NOT support PVRTC2. Therefore, we don't support them at the moment

        // Compressed ASTC formats
        ASTC_4x4_srgb,
        ASTC_5x4_srgb,
        ASTC_5x5_srgb,
        ASTC_6x5_srgb,
        ASTC_6x6_srgb,
        ASTC_8x5_srgb,
        ASTC_8x6_srgb,
        ASTC_8x8_srgb,
        ASTC_10x5_srgb,
        ASTC_10x6_srgb,
        ASTC_10x8_srgb,
        ASTC_10x10_srgb,
        ASTC_12x10_srgb,
        ASTC_12x12_srgb,

        // Compressed BC formats
        BC1_rgba,
        BC1_rgba_srgb,
        BC2_rgba,
        BC2_rgba_srgb,
        BC3_rgba,
        BC3_rgba_srgb,
        BC4_rUnorm,
        BC4_rSnorm,
        BC5_rgUnorm,
        BC5_rgSnorm,
        BC6H_rgbFloat,
        BC6H_rgbuFloat,
        BC7_rgbaUnorm,
        BC7_rgbaUnorm_srgb,

        // Depth and stencil formats
        Depth16Unorm,
        Depth32Float,
        Stencil8,
        Depth24Unorm_stencil8,
        Depth32Float_stencil8,
    };
}

#endif //GFXTK_PIXELFORMAT_HPP
