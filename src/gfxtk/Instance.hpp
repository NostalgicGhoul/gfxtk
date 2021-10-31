#ifndef GFXTK_INSTANCE_HPP
#define GFXTK_INSTANCE_HPP

#include <memory>
#include <optional>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/InstanceDescriptor.hpp>
#include <gfxtk/PixelFormat.hpp>
#include <gfxtk/ColorSpace.hpp>
#include <gfxtk/QueueFlags.hpp>
#include <gfxtk/SwapChainConfig.hpp>
#include <gfxtk/DeviceInfo.hpp>
#include <functional>

namespace gfxtk {
    class Device;
    class Window;

    namespace backend {
        struct Instance;
    }

    // NOTE: `Instance` exists as a way to make the "lifetime" of a program written with `gfxtk` easier to manage in C++
    //       The instance is the first thing you create and is what you configure. In Vulkan, it stores the `VkInstance`
    //       but this is needed for more than just `VkInstance`, it handles the cleanup of the program resources in a
    //       better order than they would occur without.
    //       In most frameworks, you just call `lib::init(...)` and then maybe `lib::terminate` or `lib::shutdown` at
    //       the end. This, in my opinion, is more of a "C-ism", it doesn't fit very well into C++. For this to work in
    //       C++ properly, you would have to set up a system to keep track of all resources allocated manually. For
    //       example, to allocate a `Device` and have it be destroyed _before_ the instance is destroyed you would have
    //       to:
    //        1. Consider keeping a list of allocated `Device`s, making it where to _actually_ destroy a device you
    //           have to manually call the destroy function (in C++ this should happen automatically when the device is
    //           no longer in use, whether from the device no longer being in scope, or all references to it being
    //           destroyed)
    //        2. Consider implementing your own allocator, basically does the same as above, it tries to hide the
    //           destruction of the device in a much more involved manner
    //       In my eyes, the simplest solution is to just require an `Instance` from which all allocations are made.
    //       This instance is what you grab a "device" from, and from there everything destructs in order. Since you
    //       need and `Instance` to create a `Device` it will then look like as follows:
    //       ```
    //       auto instance = Instance::create(ConfigStuff...);
    //       auto window = Window::create(instance, ...); // Require an instance _only_ to force the programmer to make
    //                                                    // it _after_ the instance
    //       auto device = instance.createDevice(...); // Create the device _from_ the instance now.
    //       ```
    class GFXTK_EXPORT Instance {
    public:
        static Instance create(InstanceDescriptor const& initConfig);
        Instance(Instance&& other) noexcept;
        Instance& operator=(Instance&& other) noexcept;

        /**
         * Grab the device that best fits the requirements provided by `InstanceDescriptor`. On the majority of systems, this
         * will only check that the only GPU on the machine fits the requirements. In the situation that there are
         * multiple GPUs (e.g. laptops with both integrated and dedicated GPUs) we will select the GPU that is the most
         * powerful while still supporting everything. This _does_ mean there is the possibility we will choose the
         * integrated GPU in the (unlikely) situation where the integrated GPU supports a required feature and the
         * dedicated doesn't
         *
         * @param createQueueFlags this will have the Device created with queue(s) supporting the provided flags
         *                         (e.g. Render, Compute, etc.)
         * @param swapChainConfig an optional swap chain configuration for if you want to use a swap chain for
         *                        presentation. If this is not provided, gfxtk will not attempt to set up the device
         *                        for presentation to a window.
         * @return the best fitting GPU
         */
        Device createBestFitDevice(
                QueueFlags createQueueFlags,
                std::optional<SwapChainConfig> const& swapChainConfig = std::nullopt
        );
        /**
         * Grab a information about all known GPU devices plugged in to the system that are supported by the chosen
         * backend API
         *
         * @param swapChainConfig an optional swap chain configuration for if you want to use a swap chain for
         *                        presentation. If this is not provided, gfxtk will not attempt to set up the device
         *                        for presentation to a window.
         *
         * @return a list of objects containing information on each GPU
         */
        std::vector<DeviceInfo> getDevices(std::optional<SwapChainConfig> swapChainConfig = std::nullopt);
        /**
         * Grab a specific device from a known `DeviceInfo`
         *
         * @param chosenDevice a device retrieved from `getDevices`
         * @param createQueueFlags this will have the Device created with queue(s) supporting the provided flags
         *                         (e.g. Render, Compute, etc.)
         * @return the chosen GPU device
         */
        Device createDevice(
                DeviceInfo const& chosenDevice,
                QueueFlags createQueueFlags,
                std::optional<SwapChainConfig> swapChainConfig
        );

        SwapChainConfig createSwapChainConfig(
                std::unique_ptr<Window> const& window,
                PixelFormat pixelFormat,
                ColorSpace colorSpace,
                uint32_t framesInFlight = std::numeric_limits<uint32_t>::max()
        );

        std::unique_ptr<Window> createWindow(
                std::string const& title,
                int width,
                int height,
                std::function<void(int, int)> onResized
        );

        ~Instance();

    private:
        // NOTE: There can only be ONE (1) Instance! This is required to make sure everything is destroyed properly.
        static bool hasBeenCreated;
        std::unique_ptr<backend::Instance> _backendInstance;

        explicit Instance(std::unique_ptr<backend::Instance> backendInstance);

    };
}

#endif //GFXTK_INSTANCE_HPP
