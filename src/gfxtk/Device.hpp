#ifndef GFXTK_DEVICE_HPP
#define GFXTK_DEVICE_HPP

#include <gfxtk/InstanceDescriptor.hpp>

#include <memory>
#include <optional>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/QueueFlags.hpp>
#include <gfxtk/DeviceInfo.hpp>
#include <gfxtk/SwapChain.hpp>
#include <gfxtk/SwapChainConfig.hpp>
#include <gfxtk/BindGroupLayout.hpp>
#include <gfxtk/PipelineLayout.hpp>
#include <gfxtk/RenderPassAttachmentDescriptor.hpp>
#include "RenderPassAttachment.hpp"
#include "Pipeline.hpp"
#include "CommandQueue.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "BindGroup.hpp"

namespace gfxtk {
    namespace backend {
        struct Device;
        struct Instance;
    }

    class GFXTK_EXPORT Device {
        friend class Instance;

    public:
        ~Device();

        SwapChain createSwapChain(SwapChainConfig& swapChainConfig);
        Shader createShader(std::string const& sourceFilePath);
        BindGroupLayout createBindGroupLayout(BindGroupLayoutDescriptor const& descriptor);
        RenderPassAttachment createRenderPassAttachment(RenderPassAttachmentDescriptor const& descriptor);
        PipelineLayout createPipelineLayout(std::vector<BindGroupLayout> const& bindingGroupLayouts = {});
        Pipeline createRenderPipeline(RenderPipelineDescriptor const& descriptor);
        CommandQueue createRenderCommandQueue(size_t numberCommandBuffers);
        Semaphore createSemaphore();
        Fence createFence(bool signaled);
        Buffer createBuffer(
                size_t size,
                gfxtk::BufferUsageFlags bufferUsageFlags,
                gfxtk::MemoryUsage memoryUsage
        );
        Texture createTexture(
                gfxtk::TextureType type,
                gfxtk::PixelFormat format,
                gfxtk::Extent3D extent,
                uint32_t mipLevels,
                uint32_t arrayLayers,
                gfxtk::TextureUsage usage,
                gfxtk::MemoryUsage memoryUsage
        );
        TextureView createTextureView(
                Texture& texture,
                gfxtk::TextureViewType type,
                gfxtk::PixelFormat format,
                gfxtk::TextureAspect aspect
        );
        Sampler createSampler(
                SamplerDescriptor const& descriptor
        );
        std::vector<BindGroup> createBindGroups(
                BindGroupLayout const& bindGroupLayout,
                std::vector<std::vector<BindGroupEntry>> const& groupEntries
        );

        void waitForFence(Fence const& fence, uint64_t timeout = std::numeric_limits<uint64_t>::max());
        void waitForFences(std::vector<Fence> const& fences, uint64_t timeout = std::numeric_limits<uint64_t>::max());
        void resetFence(Fence const& fence);
        void resetFences(std::vector<Fence> const& fences);

        void waitIdle();

    private:
        std::shared_ptr<backend::Device> _backendDevice;
        std::vector<QueueFamily> _chosenQueueFamilies;

        Device(std::shared_ptr<backend::Device> backendDevice, std::vector<QueueFamily> chosenQueueFamilies);

        static Device createBestFit(
                std::unique_ptr<backend::Instance> const& instance,
                QueueFlags createQueueFlags,
                std::optional<SwapChainConfig> const& swapChainConfig = std::nullopt
        );
        static std::vector<DeviceInfo> getDevices(
                std::unique_ptr<backend::Instance> const& instance,
                std::optional<SwapChainConfig> swapChainConfig = std::nullopt
        );
        static Device create(
                std::unique_ptr<backend::Instance> const& instance,
                DeviceInfo const& chosenDevice,
                QueueFlags createQueueFlags,
                std::optional<SwapChainConfig> swapChainConfig
        );

    };
}

#endif //GFXTK_DEVICE_HPP
