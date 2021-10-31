#include "BindGroup.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/BindGroup.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/BindGroup.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif


std::vector<gfxtk::BindGroup> gfxtk::BindGroup::createBindGroups(
        std::shared_ptr<backend::Device> const& backendDevice,
        std::shared_ptr<backend::BindGroupLayout> const& backendBindGroupLayout,
        std::vector<std::vector<BindGroupEntry>> const& groupEntries
) {
    std::vector<std::vector<backend::BindGroupEntry*>> backendGroupEntries;
    backendGroupEntries.reserve(groupEntries.size());

    for (auto const& frameGroupEntries : groupEntries) {
        std::vector<backend::BindGroupEntry*> frameBackendGroupEntries;
        frameBackendGroupEntries.reserve(frameGroupEntries.size());

        for (auto const& groupEntry : frameGroupEntries) {
            frameBackendGroupEntries.push_back(groupEntry._backendBindGroupEntry.get());
        }

        backendGroupEntries.push_back(frameBackendGroupEntries);
    }

    auto backendBindGroups = backend::BindGroup::createBindGroups(
            backendDevice,
            backendBindGroupLayout,
            backendGroupEntries
    );

    std::vector<BindGroup> results;
    results.reserve(backendBindGroups.size());

    for (auto const& backendBindGroup : backendBindGroups) {
        results.push_back(BindGroup(backendBindGroup));
    }

    return results;
}

gfxtk::BindGroup::BindGroup(std::shared_ptr<backend::BindGroup> backendBindGroup)
        : _backendBindGroup(std::move(backendBindGroup)) {}

gfxtk::BindGroup::~BindGroup() = default;
