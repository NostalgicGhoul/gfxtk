#ifndef GFXTK_MEMORYUSAGE_HPP
#define GFXTK_MEMORYUSAGE_HPP

namespace gfxtk {
    enum class MemoryUsage {
        Unknown = 0,
        GpuOnly,
        CpuOnly,
        CpuToGpu,
    };
}

#endif //GFXTK_MEMORYUSAGE_HPP
