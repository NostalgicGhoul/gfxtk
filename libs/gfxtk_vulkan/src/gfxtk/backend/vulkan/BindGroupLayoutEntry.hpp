#ifndef GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUTENTRY_HPP
#define GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUTENTRY_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/BindGroupLayoutEntry.hpp>

namespace gfxtk::backend {
    struct BindGroupLayoutEntry {
        static VkDescriptorType getDescriptorType(gfxtk::BindGroupLayoutEntry const& entry);

    };
}

#endif //GFXTK_BACKEND_VULKAN_BINDGROUPLAYOUTENTRY_HPP
