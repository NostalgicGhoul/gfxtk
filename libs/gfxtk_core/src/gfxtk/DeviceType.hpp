#ifndef GFXTK_DEVICETYPE_HPP
#define GFXTK_DEVICETYPE_HPP

namespace gfxtk {
    enum class DeviceType {
        Unknown = 0,
        CPU = 1,
        IntegratedGPU = 2,
        VirtualGPU = 3,
        DiscreteGPU = 4,
    };
}

#endif //GFXTK_DEVICETYPE_HPP
