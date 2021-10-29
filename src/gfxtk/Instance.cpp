#include "Instance.hpp"
#include "Window.hpp"
#include <gfxtk/log.hpp>
#include "Device.hpp"

#ifdef GFXTK_GRAPHICS_BACKEND_VULKAN
#include <gfxtk/backend/vulkan/Instance.hpp>
#elif GFXTK_GRAPHICS_BACKEND_METAL
#include <gfxtk/backend/metal/Instance.hpp>
#else
#error target OS is not supported by any existing graphics backend!
#endif

bool gfxtk::Instance::hasBeenCreated = false;

gfxtk::Instance gfxtk::Instance::create(gfxtk::InitConfig const& initConfig) {
    if (hasBeenCreated) {
        GFXTK_LOG_F("an instance already exists, only one instance can exist at a time!");
    } else {
        hasBeenCreated = true;
        log::init();
        Window::init();
    }

    GFXTK_LOG_I("initializing graphics backend...");
    return gfxtk::Instance(backend::Instance::create(initConfig));
}

gfxtk::Instance::Instance(std::unique_ptr<backend::Instance> backendInstance)
        : _backendInstance(std::move(backendInstance)) {}

gfxtk::Instance::Instance(gfxtk::Instance&& other) noexcept {
    this->_backendInstance = std::move(other._backendInstance);
}

gfxtk::Instance& gfxtk::Instance::operator=(gfxtk::Instance&& other) noexcept {
    this->_backendInstance = std::move(other._backendInstance);
    return *this;
}

gfxtk::Instance::~Instance() {
    // TODO: This isn't needed if we make it so `Instance` doesn't have a default constructor...
    if (hasBeenCreated && _backendInstance != nullptr) {
        _backendInstance = nullptr;
        Window::deinit();
        hasBeenCreated = false;
        GFXTK_LOG_I("gfxtk has shutdown.");
        log::deinit();
    }
}

gfxtk::Device gfxtk::Instance::createBestFitDevice(
        gfxtk::QueueFlags createQueueFlags,
        std::optional<SwapChainConfig> const& swapChainConfig
) {
    return Device::createBestFit(_backendInstance, createQueueFlags, swapChainConfig);
}

std::vector<gfxtk::DeviceInfo> gfxtk::Instance::getDevices(std::optional<SwapChainConfig> swapChainConfig) {
    return Device::getDevices(_backendInstance, std::move(swapChainConfig));
}

gfxtk::Device gfxtk::Instance::createDevice(
        gfxtk::DeviceInfo const& chosenDevice,
        gfxtk::QueueFlags createQueueFlags,
        std::optional<SwapChainConfig> swapChainConfig
) {
    return Device::create(
            _backendInstance,
            chosenDevice,
            createQueueFlags,
            std::move(swapChainConfig)
    );
}

gfxtk::SwapChainConfig gfxtk::Instance::createSwapChainConfig(
        std::unique_ptr<Window> const& window,
        gfxtk::PixelFormat pixelFormat,
        gfxtk::ColorSpace colorSpace,
        uint32_t framesInFlight
) {
    return gfxtk::SwapChainConfig::create(_backendInstance, window, pixelFormat, colorSpace, framesInFlight);
}

std::unique_ptr<gfxtk::Window> gfxtk::Instance::createWindow(
        std::string const& title,
        int width,
        int height,
        std::function<void(int, int)> onResized
) {
    return Window::create(title, width, height, std::move(onResized));
}
