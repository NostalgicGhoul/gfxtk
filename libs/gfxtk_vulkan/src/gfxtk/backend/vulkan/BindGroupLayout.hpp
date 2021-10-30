#ifndef GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUT_HPP
#define GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUT_HPP

#ifdef GFXTK_BACKEND_VULKAN_INTERNAL
#define WINDOWS_SUCKS __declspec(dllexport)
#else
#define WINDOWS_SUCKS __declspec(dllimport)
#endif

#include <vulkan/vulkan.h>
#include <memory>
#include <gfxtk/BindGroupLayoutDescriptor.hpp>
#include "Device.hpp"

namespace gfxtk::backend {
    struct BindGroupLayout {
        static std::shared_ptr<BindGroupLayout> create(
                std::shared_ptr<backend::Device> const& backendDevice,
                BindGroupLayoutDescriptor const& descriptor
        );

        VkDevice vulkanDevice;
        VkDescriptorSetLayout vulkanDescriptorSetLayout;

        BindGroupLayout(VkDevice vulkanDevice, VkDescriptorSetLayout vulkanDescriptorSetLayout);
        ~BindGroupLayout();

    };
}

#endif //GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUT_HPP
