#include <gfxtk/log.hpp>
#include "MemoryUsage.hpp"

VmaMemoryUsage gfxtk::backend::MemoryUsage::convert(gfxtk::MemoryUsage memoryUsage) {
    switch (memoryUsage) {
        case gfxtk::MemoryUsage::Unknown:
            return VMA_MEMORY_USAGE_UNKNOWN;
        case gfxtk::MemoryUsage::GpuOnly:
            return VMA_MEMORY_USAGE_GPU_ONLY;
        case gfxtk::MemoryUsage::CpuOnly:
            return VMA_MEMORY_USAGE_CPU_ONLY;
        case gfxtk::MemoryUsage::CpuToGpu:
            return VMA_MEMORY_USAGE_CPU_TO_GPU;
        default:
            GFXTK_LOG_F("unknown `MemoryUsage` passed to `gfxtk::backend::MemoryUsage::convert`!");
    }
}
