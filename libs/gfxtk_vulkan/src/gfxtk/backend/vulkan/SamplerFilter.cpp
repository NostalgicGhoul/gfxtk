#include "SamplerFilter.hpp"

VkFilter gfxtk::backend::SamplerFilter::convert(gfxtk::SamplerFilter samplerFilter) {
    switch (samplerFilter) {
        case gfxtk::SamplerFilter::Nearest:
            return VK_FILTER_NEAREST;
        case gfxtk::SamplerFilter::Linear:
            return VK_FILTER_LINEAR;
    }
}
