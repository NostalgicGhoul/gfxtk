#include <gfxtk/log.hpp>
#include "Sampler.hpp"
#include "SamplerFilter.hpp"
#include "SamplerMipmapMode.hpp"
#include "SamplerAddressMode.hpp"

std::shared_ptr<gfxtk::backend::Sampler> gfxtk::backend::Sampler::create(
        std::shared_ptr<backend::Device> const& backendDevice,
        gfxtk::SamplerDescriptor const& samplerDescriptor
) {
    VkSamplerCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    createInfo.magFilter = backend::SamplerFilter::convert(samplerDescriptor.magFilter);
    createInfo.minFilter = backend::SamplerFilter::convert(samplerDescriptor.minFilter);
    createInfo.mipmapMode = backend::SamplerMipmapMode::convert(samplerDescriptor.mipmapMode);
    createInfo.addressModeU = backend::SamplerAddressMode::convert(samplerDescriptor.addressModeU);
    createInfo.addressModeV = backend::SamplerAddressMode::convert(samplerDescriptor.addressModeV);
    createInfo.addressModeW = backend::SamplerAddressMode::convert(samplerDescriptor.addressModeW);
    createInfo.mipLodBias = 0;
    createInfo.anisotropyEnable = samplerDescriptor.isAnisotropyEnabled;
    createInfo.maxAnisotropy = samplerDescriptor.maxAnisotropy;
    createInfo.compareEnable = samplerDescriptor.isCompareEnabled;
    createInfo.compareOp = backend::CompareOp::convert(samplerDescriptor.compareOp);
    createInfo.minLod = samplerDescriptor.minLod;
    createInfo.maxLod = samplerDescriptor.maxLod;
    createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    createInfo.unnormalizedCoordinates = !samplerDescriptor.normalizedCoordinates;

    VkSampler textureSampler;

    if (vkCreateSampler(backendDevice->logicalDevice, &createInfo, nullptr, &textureSampler) != VK_SUCCESS) {
        GFXTK_LOG_F("failed to create `Sampler` on Vulkan backend!");
    }

    return std::make_shared<Sampler>(backendDevice->logicalDevice, textureSampler);
}
