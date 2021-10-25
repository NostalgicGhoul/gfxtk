#ifndef GFXTK_SAMPLECOUNT_HPP
#define GFXTK_SAMPLECOUNT_HPP

namespace gfxtk {
    enum class SampleCount {
        Count1 = 0x01,
        Count2 = 0x02,
        Count4 = 0x04,
        Count8 = 0x08,
        Count16 = 0x10,
        Count32 = 0x20,
        Count64 = 0x40,
    };
}

#endif //GFXTK_SAMPLECOUNT_HPP
