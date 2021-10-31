#ifndef GFXTK_BINDGROUP_HPP
#define GFXTK_BINDGROUP_HPP

#include <memory>
#include <vector>
#include <gfxtk/gfxtk_internal.hpp>
#include "BindGroupEntry.hpp"

namespace gfxtk {
    namespace backend {
        struct BindGroup;
        struct BindGroupLayout;
        struct Device;
    }

    class GFXTK_EXPORT BindGroup {
        friend class Device;
        friend class RenderPassEncoder;

    public:
        ~BindGroup();

    private:
        static std::vector<BindGroup> createBindGroups(
                std::shared_ptr<backend::Device> const& backendDevice,
                std::shared_ptr<backend::BindGroupLayout> const& backendBindGroupLayout,
                std::vector<std::vector<BindGroupEntry>> const& groupEntries
        );

        std::shared_ptr<backend::BindGroup> _backendBindGroup;

        explicit BindGroup(std::shared_ptr<backend::BindGroup> backendBindGroup);

    };
}

#endif //GFXTK_BINDGROUP_HPP
