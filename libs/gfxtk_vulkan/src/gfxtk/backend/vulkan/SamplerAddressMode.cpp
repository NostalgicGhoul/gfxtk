#include "SamplerAddressMode.hpp"

VkSamplerAddressMode gfxtk::backend::SamplerAddressMode::convert(gfxtk::SamplerAddressMode samplerAddressMode) {
    switch (samplerAddressMode) {
        case gfxtk::SamplerAddressMode::Repeat:
            return VK_SAMPLER_ADDRESS_MODE_REPEAT;
        case gfxtk::SamplerAddressMode::MirrorRepeat:
            return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
        case gfxtk::SamplerAddressMode::ClampToEdge:
            return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        case gfxtk::SamplerAddressMode::ClampToBorder:
            return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
    }
}
