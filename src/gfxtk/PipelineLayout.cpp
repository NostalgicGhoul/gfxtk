#include "PipelineLayout.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/PipelineLayout.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

gfxtk::PipelineLayout gfxtk::PipelineLayout::create(
        std::shared_ptr<backend::Device> const& device,
        std::vector<BindGroupLayout> const& bindingGroupLayouts
) {
    std::vector<backend::BindGroupLayout*> backendBindingGroupLayouts;
    backendBindingGroupLayouts.reserve(bindingGroupLayouts.size());

    for (auto const& bindingGroupLayout : bindingGroupLayouts) {
        backendBindingGroupLayouts.push_back(bindingGroupLayout._backendBindGroupLayout.get());
    }

    return gfxtk::PipelineLayout(backend::PipelineLayout::create(device, backendBindingGroupLayouts));
}

gfxtk::PipelineLayout::PipelineLayout(std::shared_ptr<backend::PipelineLayout> backendPipelineLayout)
        : _backendPipelineLayout(std::move(backendPipelineLayout)) {}

gfxtk::PipelineLayout::~PipelineLayout() = default;
