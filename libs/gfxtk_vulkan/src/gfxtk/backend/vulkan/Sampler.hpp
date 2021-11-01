#ifndef GFXTK_BACKEND_VULKAN_SAMPLER_HPP
#define GFXTK_BACKEND_VULKAN_SAMPLER_HPP

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/SamplerFilter.hpp>
#include <gfxtk/SamplerMipmapMode.hpp>
#include <gfxtk/SamplerAddressMode.hpp>
#include <gfxtk/SamplerDescriptor.hpp>
#include "Device.hpp"
#include "CompareOp.hpp"

namespace gfxtk::backend {
    struct Sampler {
        static std::shared_ptr<Sampler> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                SamplerDescriptor const& samplerDescriptor
        );

        VkDevice vulkanDevice;
        VkSampler vulkanSampler;

        Sampler(VkDevice vulkanDevice, VkSampler vulkanSampler)
                : vulkanDevice(vulkanDevice), vulkanSampler(vulkanSampler) {}
        ~Sampler() {
            vkDestroySampler(vulkanDevice, vulkanSampler, nullptr);
        }

    };
}

#endif //GFXTK_BACKEND_VULKAN_SAMPLER_HPP
