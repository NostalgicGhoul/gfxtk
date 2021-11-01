#ifndef GFXTK_SAMPLERDESCRIPTOR_HPP
#define GFXTK_SAMPLERDESCRIPTOR_HPP

#include "microsoft_fix.hpp"
#include "SamplerFilter.hpp"
#include "SamplerAddressMode.hpp"
#include "SamplerMipmapMode.hpp"
#include "CompareOp.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT SamplerDescriptor {
        SamplerFilter magFilter;
        SamplerFilter minFilter;
        SamplerAddressMode addressModeU;
        SamplerAddressMode addressModeV;
        SamplerAddressMode addressModeW;
        SamplerMipmapMode mipmapMode;
        bool isAnisotropyEnabled;
        float maxAnisotropy;
        bool isCompareEnabled;
        CompareOp compareOp;
        float minLod;
        float maxLod;
        bool normalizedCoordinates;

        SamplerDescriptor(
                SamplerFilter magFilter,
                SamplerFilter minFilter,
                SamplerAddressMode addressModeU,
                SamplerAddressMode addressModeV,
                SamplerAddressMode addressModeW,
                SamplerMipmapMode mipmapMode = SamplerMipmapMode::Nearest,
                bool isAnisotropyEnabled = false,
                float maxAnisotropy = 0,
                bool isCompareEnabled = false,
                CompareOp compareOp = CompareOp::Never,
                float minLod = 0,
                float maxLod = 0,
                bool normalizedCoordinates = true
        ) : magFilter(magFilter),
            minFilter(minFilter),
            addressModeU(addressModeU),
            addressModeV(addressModeV),
            addressModeW(addressModeW),
            mipmapMode(mipmapMode),
            isAnisotropyEnabled(isAnisotropyEnabled),
            maxAnisotropy(maxAnisotropy),
            isCompareEnabled(isCompareEnabled),
            compareOp(compareOp),
            minLod(minLod),
            maxLod(maxLod),
            normalizedCoordinates(normalizedCoordinates) {}

    };
}

#endif //GFXTK_SAMPLERDESCRIPTOR_HPP
