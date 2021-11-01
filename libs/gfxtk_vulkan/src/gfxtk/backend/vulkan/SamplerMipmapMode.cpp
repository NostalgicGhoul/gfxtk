#include "SamplerMipmapMode.hpp"

VkSamplerMipmapMode gfxtk::backend::SamplerMipmapMode::convert(gfxtk::SamplerMipmapMode samplerMipmapMode) {
    switch (samplerMipmapMode) {
        case gfxtk::SamplerMipmapMode::Linear:
            return VK_SAMPLER_MIPMAP_MODE_LINEAR;
        case gfxtk::SamplerMipmapMode::Nearest:
            return VK_SAMPLER_MIPMAP_MODE_NEAREST;
    }
}
