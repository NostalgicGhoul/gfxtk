#include "SampleCount.hpp"

VkSampleCountFlagBits gfxtk::backend::SampleCount::convert(gfxtk::SampleCount sampleCount) {
    switch (sampleCount) {
        case gfxtk::SampleCount::Count1:
            return VK_SAMPLE_COUNT_1_BIT;
        case gfxtk::SampleCount::Count2:
            return VK_SAMPLE_COUNT_2_BIT;
        case gfxtk::SampleCount::Count4:
            return VK_SAMPLE_COUNT_4_BIT;
        case gfxtk::SampleCount::Count8:
            return VK_SAMPLE_COUNT_8_BIT;
        case gfxtk::SampleCount::Count16:
            return VK_SAMPLE_COUNT_16_BIT;
        case gfxtk::SampleCount::Count32:
            return VK_SAMPLE_COUNT_32_BIT;
        case gfxtk::SampleCount::Count64:
            return VK_SAMPLE_COUNT_64_BIT;
    }
}
