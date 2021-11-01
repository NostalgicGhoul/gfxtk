#ifndef GFXTK_BACKEND_VULKAN_ACCESSFLAGS_HPP
#define GFXTK_BACKEND_VULKAN_ACCESSFLAGS_HPP

#include <vulkan/vulkan.h>
#include <gfxtk/AccessFlags.hpp>

namespace gfxtk::backend {
    struct AccessFlags {
        static VkAccessFlags convert(gfxtk::AccessFlags accessFlags);

    };
}

#endif //GFXTK_BACKEND_VULKAN_ACCESSFLAGS_HPP
