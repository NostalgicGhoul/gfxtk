#include "Device.hpp"
#include <vector>
#include <gfxtk/log.hpp>
#include "Instance.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Device.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/Device.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

#ifdef GFXTK_WINDOW_BACKEND_GLFW
#include <gfxtk/backend/glfw/Window.hpp>
#else
#error target OS is not supported by any existing window backend!
#endif

gfxtk::Device gfxtk::Device::createBestFit(
        std::unique_ptr<backend::Instance> const& instance,
        QueueFlags createQueueFlags,
        std::optional<SwapChainConfig> const& swapChainConfig
) {
    auto allDevices = getDevices(instance, swapChainConfig);

    // TODO: Regardless of how many devices there are, we must ONLY return a device if _everything_ requested is
    //       supported by that device. That means if the only device in the system _doesn't_ support everything then
    //       we abort.
    if (allDevices.size() == 1) {
        return create(instance, allDevices[0], createQueueFlags, swapChainConfig);
    } else if (allDevices.size() > 1) {
        // TODO: For now, choose the first dedicated we can find. Later we need to create a system to rate systems
        //       based on how powerful they are
    }

    GFXTK_LOG_F("no GPU devices were found!");
}

std::vector<gfxtk::DeviceInfo> gfxtk::Device::getDevices(
        std::unique_ptr<backend::Instance> const& instance,
        std::optional<SwapChainConfig> swapChainConfig
) {
    if (swapChainConfig.has_value()) {
        return backend::Device::getDevices(instance, swapChainConfig->_backendSwapChainConfig.get());
    } else {
        return backend::Device::getDevices(instance, nullptr);
    }
}

gfxtk::Device gfxtk::Device::create(
        std::unique_ptr<backend::Instance> const& instance,
        gfxtk::DeviceInfo const& chosenDevice,
        gfxtk::QueueFlags createQueueFlags,
        std::optional<SwapChainConfig> swapChainConfig
) {
    // If `Render` wasn't requested then we automatically set `renderFound` to true, same for the rest
    bool renderFound = (createQueueFlags & QueueFlags::Render) == QueueFlags::None;
    bool computeFound = (createQueueFlags & QueueFlags::Compute) == QueueFlags::None;
    bool presentFound = (createQueueFlags & QueueFlags::Present) == QueueFlags::None;
    std::vector<QueueFamily> chosenQueueFamilies;

    for (auto const& queueFamily : chosenDevice.queueFamilies()) {
        bool shouldAddQueue = false;

        if (!renderFound && (createQueueFlags & QueueFlags::Render) == QueueFlags::Render) {
            shouldAddQueue = true;
            renderFound = true;
        }

        if (!computeFound && (createQueueFlags & QueueFlags::Compute) == QueueFlags::Compute) {
            shouldAddQueue = true;
            computeFound = true;
        }

        if (!presentFound && (createQueueFlags & QueueFlags::Present) == QueueFlags::Present) {
            shouldAddQueue = true;
            presentFound = true;
        }

        if (shouldAddQueue) {
            chosenQueueFamilies.push_back(queueFamily);
        }

        if (renderFound && computeFound && presentFound) {
            break;
        }
    }

    if (!renderFound) {
        GFXTK_LOG_F("the requested device does not support render queues!");
    }

    if (!computeFound) {
        GFXTK_LOG_F("the requested device does not support compute queues!");
    }

    if (!presentFound) {
        GFXTK_LOG_F("the requested device does not support presentation queues!");
    }

    if (swapChainConfig.has_value()) {
        return Device(
                backend::Device::create(
                        instance,
                        chosenDevice,
                        chosenQueueFamilies,
                        swapChainConfig->_backendSwapChainConfig.get()
                ),
                chosenQueueFamilies
        );
    } else {
        return Device(
                backend::Device::create(
                        instance,
                        chosenDevice,
                        chosenQueueFamilies,
                        nullptr
                ),
                chosenQueueFamilies
        );
    }
}

gfxtk::Device::Device(std::shared_ptr<backend::Device> backendDevice, std::vector<QueueFamily> chosenQueueFamilies)
        : _backendDevice(std::move(backendDevice)), _chosenQueueFamilies(std::move(chosenQueueFamilies)) {}

gfxtk::Device::~Device() = default;

gfxtk::SwapChain gfxtk::Device::createSwapChain(SwapChainConfig& swapChainConfig) {
    return gfxtk::SwapChain::create(
            _backendDevice,
            _chosenQueueFamilies,
            swapChainConfig._backendSwapChainConfig
    );
}

gfxtk::Shader gfxtk::Device::createShader(std::string const& sourceFilePath) {
    return Shader::createFromSource(_backendDevice, sourceFilePath);
}

gfxtk::BindGroupLayout gfxtk::Device::createBindGroupLayout(BindGroupLayoutDescriptor const& descriptor) {
    return BindGroupLayout::create(_backendDevice, descriptor);
}

gfxtk::RenderPassAttachment gfxtk::Device::createRenderPassAttachment(
        gfxtk::RenderPassAttachmentDescriptor const& descriptor
) {
    return gfxtk::RenderPassAttachment::create(_backendDevice, descriptor);
}

gfxtk::PipelineLayout gfxtk::Device::createPipelineLayout(std::vector<BindGroupLayout> const& bindingGroupLayouts) {
    return gfxtk::PipelineLayout::create(_backendDevice, bindingGroupLayouts);
}

gfxtk::Pipeline gfxtk::Device::createRenderPipeline(gfxtk::RenderPipelineDescriptor const& descriptor) {
    return gfxtk::Pipeline::createRenderPipeline(_backendDevice, descriptor);
}

gfxtk::QueueFamily const& findRenderQueueFamily(std::vector<gfxtk::QueueFamily> const& chosenQueueFamilies) {
    for (auto const& checkFamily : chosenQueueFamilies) {
        if ((checkFamily.flags() & gfxtk::QueueFlags::Render) == gfxtk::QueueFlags::Render) {
            return checkFamily;
        }
    }

    GFXTK_LOG_F("render queue family was not found! (did you request it when creating the device?)");
}

gfxtk::CommandQueue gfxtk::Device::createRenderCommandQueue(size_t numberCommandBuffers) {
    return gfxtk::CommandQueue::createRenderCommandQueue(
            _backendDevice,
            numberCommandBuffers,
            findRenderQueueFamily(_chosenQueueFamilies)
    );
}

gfxtk::Semaphore gfxtk::Device::createSemaphore() {
    return gfxtk::Semaphore::create(_backendDevice);
}

gfxtk::Fence gfxtk::Device::createFence(bool signaled) {
    return gfxtk::Fence::create(_backendDevice, signaled);
}

gfxtk::Buffer gfxtk::Device::createBuffer(
        size_t size,
        gfxtk::BufferUsageFlags bufferUsageFlags,
        gfxtk::MemoryUsage memoryUsage
) {
    return gfxtk::Buffer::create(_backendDevice, size, bufferUsageFlags, memoryUsage);
}

gfxtk::Texture gfxtk::Device::createTexture(
        gfxtk::TextureType type,
        gfxtk::PixelFormat format,
        gfxtk::Extent3D extent,
        uint32_t mipLevels,
        uint32_t arrayLayers,
        gfxtk::TextureUsage usage,
        gfxtk::MemoryUsage memoryUsage
) {
    return gfxtk::Texture::create(
            _backendDevice,
            type,
            format,
            extent,
            mipLevels,
            arrayLayers,
            usage,
            memoryUsage
    );
}

gfxtk::TextureView gfxtk::Device::createTextureView(
        gfxtk::Texture& texture,
        gfxtk::TextureViewType type,
        gfxtk::PixelFormat format,
        gfxtk::TextureAspect aspect
) {
    return gfxtk::TextureView::create(
            _backendDevice,
            texture._backendTexture,
            type,
            format,
            aspect
    );
}

gfxtk::Sampler gfxtk::Device::createSampler(gfxtk::SamplerDescriptor const& descriptor) {
    return gfxtk::Sampler::create(_backendDevice, descriptor);
}

std::vector<gfxtk::BindGroup> gfxtk::Device::createBindGroups(
        gfxtk::BindGroupLayout const& bindGroupLayout,
        std::vector<std::vector<gfxtk::BindGroupEntry>> const& groupEntries
) {
    return BindGroup::createBindGroups(_backendDevice, bindGroupLayout._backendBindGroupLayout, groupEntries);
}

void gfxtk::Device::waitForFence(gfxtk::Fence const& fence, uint64_t timeout) {
    _backendDevice->waitForFence(fence._backendFence, timeout);
}

void gfxtk::Device::waitForFences(std::vector<Fence> const& fences, uint64_t timeout) {
    std::vector<std::shared_ptr<backend::Fence>> backendFences;
    backendFences.reserve(fences.size());

    for (auto const& fence : fences) {
        backendFences.push_back(fence._backendFence);
    }

    _backendDevice->waitForFences(backendFences, timeout);
}

void gfxtk::Device::resetFence(gfxtk::Fence const& fence) {
    _backendDevice->resetFence(fence._backendFence);
}

void gfxtk::Device::resetFences(std::vector<Fence> const& fences) {
    std::vector<std::shared_ptr<backend::Fence>> backendFences;
    backendFences.reserve(fences.size());

    for (auto const& fence : fences) {
        backendFences.push_back(fence._backendFence);
    }

    _backendDevice->resetFences(backendFences);
}

void gfxtk::Device::waitIdle() {
    _backendDevice->waitIdle();
}
