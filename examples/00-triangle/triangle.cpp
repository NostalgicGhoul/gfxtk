#include <gfxtk/log.hpp>
#include <gfxtk/Instance.hpp>
#include <gfxtk/Window.hpp>
#include <gfxtk/Device.hpp>
#include <gfxtk/SwapChainConfig.hpp>
#include <gfxtk/ShaderLibrary.hpp>
#include <gfxtk/Shader.hpp>
#include <fstream>
#include "Vertex.hpp"
#include <gfxtk/backend/vulkan/Framebuffer.hpp>

// TODO: Tasks:
//        1. [DONE] Implement the code for choosing the windowing backend, graphics backend, etc.
//        2. Finish getting a triangle rendering in the Vulkan backend
//        3. Rename `InitConfig` to `InstanceConfig`

using namespace gfxtk;

const std::vector<Vertex> vertices = {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

std::vector<char> readEntireFile(std::string const& filepath) {
    std::ifstream inputShaderStream(filepath, std::ios::binary);

    if (!inputShaderStream.good()) {
        GFXTK_LOG_F("file path `" + filepath + "` was not found!");
    }

    return std::vector<char>(std::istreambuf_iterator<char>(inputShaderStream), {});
}

void createSwapChain(
        std::unique_ptr<Window> const& window,
        Device& device,
        SwapChainConfig& swapChainConfig,
        SwapChain& swapChain,
        RenderPassAttachment& renderPassAttachment,
        Pipeline& renderPipeline,
        CommandQueue& renderCommandQueue
) {
    device.waitIdle();

    // This triggers everything to be freed...
    renderCommandQueue = {};
    renderPipeline = {};
    renderPassAttachment = {};
    swapChain = {};

    swapChain = device.createSwapChain(swapChainConfig);
    auto defaultShaderLibrary = device.createShaderLibrary();
    auto vertexShader = defaultShaderLibrary.createShader(
            "default_vertex",
            readEntireFile("shaders/shader.vert.spv")
    );
    auto fragmentShader = defaultShaderLibrary.createShader(
            "default_fragment",
            readEntireFile("shaders/shader.frag.spv")
    );
    auto pipelineLayout = device.createPipelineLayout();
    renderPassAttachment = device.createRenderPassAttachment(
            RenderPassAttachmentDescriptor(
                    {
                            RenderPassColorAttachment(
                                    PixelFormat::BGRA8Unorm_srgb,
                                    LoadOp::Clear,
                                    gfxtk::StoreOp::Store,
                                    TextureLayout::Undefined,
                                    TextureLayout::PresentSource
                            )
                    }
            )
    );
    renderPipeline = device.createRenderPipeline(
            RenderPipelineDescriptor(
                    pipelineLayout,
                    renderPassAttachment,
                    vertexShader,
                    fragmentShader,
                    PipelineVertexInputStateDescriptor(
                            {
                                    Vertex::getVertexBufferLayout()
                            }
                    ),
                    PrimitiveTopology::Triangle,
                    PipelineViewportStateDescriptor(
                            Viewport(
                                    0, 0,
                                    static_cast<float>(window->getWidth()), static_cast<float>(window->getHeight()),
                                    0, 1
                            ),
                            Rect2D(0, 0, window->getWidth(), window->getHeight())
                    ),
                    PipelineRasterizationStateDescriptor(
                            DepthClipMode::Clip,
                            TriangleFillMode::Fill,
                            CullMode::Back,
                            Winding::Clockwise
                    ),
                    {
                            PipelineColorBlendAttachmentDescriptor(ColorWriteMask::All)
                    }
            )
    );
    swapChain.configureFramebuffers(renderPassAttachment);
    // NOTE: Currently I just assume the render queue is the same as the present queue. This isn't true for 100% of
    //       devices but :shrug:
    renderCommandQueue = device.createRenderCommandQueue(swapChain);
}

int main() {
    InitConfig initConfig;
    initConfig.applicationName = "Hokari";
    initConfig.applicationVersion = Version(0, 0, 1);
    initConfig.engineName = "Hokari(backend: gfxtk)";
    initConfig.engineVersion = Version(0, 0, 1);
#ifndef NDEBUG
    initConfig.debugMode = true;
#endif

    bool framebufferResized = false;

    auto instance = Instance::create(initConfig);
    auto window = instance.createWindow(
            "Hokari", 800, 600,
            [&](int width, int height) {
                framebufferResized = true;
            }
    );
    auto swapChainConfig = instance.createSwapChainConfig(
            window,
            PixelFormat::BGRA8Unorm_srgb,
            ColorSpace::SRGB
    );
    auto device = instance.createBestFitDevice(QueueFlags::Render | QueueFlags::Present, swapChainConfig);
    SwapChain swapChain;
    RenderPassAttachment renderPassAttachment;
    Pipeline renderPipeline;
    CommandQueue renderCommandQueue;

    createSwapChain(
            window,
            device,
            swapChainConfig,
            swapChain,
            renderPassAttachment,
            renderPipeline,
            renderCommandQueue
    );

    std::vector<Semaphore> imageAvailableSemaphores;
    std::vector<Semaphore> renderFinishedSemaphores;
    std::vector<Fence> inFlightFences;
    imageAvailableSemaphores.reserve(swapChain.framesInFlight());
    renderFinishedSemaphores.reserve(swapChain.framesInFlight());
    inFlightFences.reserve(swapChain.framesInFlight());

    for (size_t i = 0; i < swapChain.framesInFlight(); ++i) {
        imageAvailableSemaphores.push_back(device.createSemaphore());
        renderFinishedSemaphores.push_back(device.createSemaphore());
        inFlightFences.push_back(device.createFence(true));
    }

    Buffer vertexBuffer = device.createBuffer(
            sizeof(vertices[0]) * vertices.size(),
            BufferUsageFlags::Vertex,
            MemoryUsage::CpuToGpu
    );
    void* mappedBuffer = vertexBuffer.map();
    memcpy(mappedBuffer, vertices.data(), sizeof(vertices[0]) * vertices.size());
    vertexBuffer.unmap();

    while (!window->getShouldClose()) {
        Window::pollEvents();

        auto currentFrameIndex = swapChain.currentFrameIndex();
        device.waitForFence(inFlightFences[currentFrameIndex]);
        auto currentFramebuffer = swapChain.nextFramebuffer(
                imageAvailableSemaphores[currentFrameIndex],
                inFlightFences[currentFrameIndex]
        );

        if (currentFramebuffer.frameBufferErrors() == FramebufferErrors::OutOfDate || framebufferResized) {
            // If the frame was out of date then we recreate the entire swap chain as the surface most likely changed.
            createSwapChain(
                    window,
                    device,
                    swapChainConfig,
                    swapChain,
                    renderPassAttachment,
                    renderPipeline,
                    renderCommandQueue
            );
            continue;
        }

        auto currentCommandBuffer = renderCommandQueue.getCommandBufferForFrame(currentFramebuffer);
        auto currentCommandEncoder = currentCommandBuffer.beginCommandEncoding();
        auto currentRenderPassEncoder = currentCommandEncoder.beginRenderPass(
                renderPassAttachment,
                currentFramebuffer,
                Rect2D(
                        0, 0,
                        window->getWidth(), window->getHeight()
                ),
                ClearColorValue(1, 0, 1, 1)
        );

        currentRenderPassEncoder.setPipeline(renderPipeline);
        currentRenderPassEncoder.setVertexBuffer(0, vertexBuffer);
        currentRenderPassEncoder.draw(vertices.size());

        currentRenderPassEncoder.endRenderPass();
        currentCommandEncoder.endCommandEncoding();

        device.resetFence(inFlightFences[currentFrameIndex]);

        renderCommandQueue.submit(
                imageAvailableSemaphores[currentFrameIndex],
                PipelineStage::TopOfPipe,
                currentCommandBuffer,
                renderFinishedSemaphores[currentFrameIndex],
                inFlightFences[currentFrameIndex]
        );

        auto presentationErrors = renderCommandQueue.present(
                renderFinishedSemaphores[currentFrameIndex],
                swapChain,
                currentFramebuffer
        );

        if (presentationErrors == PresentationErrors::OutOfDate || framebufferResized) {
            createSwapChain(
                    window,
                    device,
                    swapChainConfig,
                    swapChain,
                    renderPassAttachment,
                    renderPipeline,
                    renderCommandQueue
            );
        }
    }

    // Let everything finish on the device before exiting...
    device.waitIdle();

    return 0;
}
