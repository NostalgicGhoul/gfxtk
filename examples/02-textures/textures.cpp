#include <gfxtk/gfxtk.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include "Vertex.hpp"
#include "UniformBufferObject.hpp"
#include "stb_image.h"

using namespace gfxtk;

void createSwapChain(
        std::unique_ptr<Window> const& window,
        Device& device,
        SwapChainConfig& swapChainConfig,
        SwapChain& swapChain,
        RenderPassAttachment& renderPassAttachment,
        BindGroupLayout const& uboBindGroupLayout,
        PipelineLayout& renderPipelineLayout,
        Pipeline& renderPipeline,
        CommandQueue& renderCommandQueue
) {
    device.waitIdle();

    // This triggers everything to be freed...
    renderCommandQueue = {};
    renderPipeline = {};
    renderPipelineLayout = {};
    renderPassAttachment = {};
    swapChain = {};

    swapChain = device.createSwapChain(swapChainConfig);
    auto vertexShader = device.createShader("shaders/shader.vert");
    auto fragmentShader = device.createShader("shaders/shader.frag");
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
    renderPipelineLayout = device.createPipelineLayout(
            {
                    uboBindGroupLayout
            }
    );
    renderPipeline = device.createRenderPipeline(
            RenderPipelineDescriptor(
                    renderPipelineLayout,
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
                            Winding::CounterClockwise
                    ),
                    {
                            PipelineColorBlendAttachmentDescriptor(ColorWriteMask::All)
                    }
            )
    );
    swapChain.configureFramebuffers(renderPassAttachment);
    renderCommandQueue = device.createRenderCommandQueue(swapChain.framesInFlight());
}

void updateUniformBuffer(Buffer& uniformBuffer, int width, int height) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    void* mappedUBO = uniformBuffer.map();
    memcpy(mappedUBO, &ubo, sizeof(ubo));
    uniformBuffer.unmap();
}

Texture createTexture(Device& device, std::string const& texturePath) {
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(texturePath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    size_t imageSize = texWidth * texHeight * 4;

    if (!pixels) {
        GFXTK_LOG_F("failed to load texture image!");
    }

    auto stagingBuffer = device.createBuffer(imageSize, BufferUsageFlags::TransferSource, MemoryUsage::CpuToGpu);

    void* mapMem = stagingBuffer.map();
    memcpy(mapMem, pixels, imageSize);
    stagingBuffer.unmap();
    stbi_image_free(pixels);

    Texture resultTexture = device.createTexture(
            TextureType::Type2D,
            PixelFormat::RGBA8Unorm_srgb,
            Extent3D(texWidth, texHeight, 1),
            1,
            1,
            TextureUsage::TransferDestination | TextureUsage::Sampled,
            MemoryUsage::GpuOnly
    );

    auto singleCommandFence = device.createFence(false);
    auto singleCommandQueue = device.createRenderCommandQueue(1);
    auto singleCommandBuffer = singleCommandQueue.getCommandBuffer(0);
    auto singleCommandEncoder = singleCommandBuffer.beginCommandEncoding();
    singleCommandEncoder.copyBufferToTexture(
            ImageCopyBuffer(stagingBuffer, 0, 0, 0),
            ImageCopyTexture(
                    resultTexture,
                    PipelineStage::FragmentShader,
                    TextureLayout::ShaderReadOnly,
                    TextureAspect::ColorOnly
            ),
            Extent3D(texWidth, texHeight, 1)
    );
    singleCommandEncoder.endCommandEncoding();
    singleCommandQueue.submit(
            singleCommandBuffer,
            singleCommandFence
    );
    device.waitForFence(singleCommandFence);

    return resultTexture;
}

int main() {
    const std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
    };
    const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
    };

    InstanceDescriptor instanceDescriptor;
    instanceDescriptor.applicationName = "Example 01: Uniform Buffer";
    instanceDescriptor.applicationVersion = Version(0, 0, 1);
    instanceDescriptor.engineName = "gfxtk";
    instanceDescriptor.engineVersion = Version(0, 0, 1);
#ifndef NDEBUG
    instanceDescriptor.debugMode = true;
#endif

    bool framebufferResized = false;

    auto instance = Instance::create(instanceDescriptor);
    auto window = instance.createWindow(
            "Triangle", 800, 600,
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
    PipelineLayout renderPipelineLayout;
    BindGroupLayout uboBindGroupLayout = device.createBindGroupLayout(
            BindGroupLayoutDescriptor(
                    {
                            BindGroupLayoutEntry(
                                    0,
                                    ShaderStageFlags::Vertex,
                                    BufferBindingLayout(BufferBindingType::Uniform)
                            ),
                            BindGroupLayoutEntry(
                                    1,
                                    ShaderStageFlags::Fragment,
                                    CombinedTextureSamplerBindingLayout()
                            )
                    }
            )
    );
    Pipeline renderPipeline;
    CommandQueue renderCommandQueue;

    createSwapChain(
            window,
            device,
            swapChainConfig,
            swapChain,
            renderPassAttachment,
            uboBindGroupLayout,
            renderPipelineLayout,
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

    Buffer indexBuffer = device.createBuffer(
            sizeof(indices[0]) * indices.size(),
            BufferUsageFlags::Index,
            // For most cases, an index buffer can be `GpuOnly` but I'm too lazy to create a staging buffer atm.
            MemoryUsage::CpuToGpu
    );
    mappedBuffer = indexBuffer.map();
    memcpy(mappedBuffer, indices.data(), sizeof(indices[0]) * indices.size());
    indexBuffer.unmap();

    // Create a uniform buffer per frame.
    std::vector<Buffer> uniformBuffers;
    uniformBuffers.reserve(swapChain.framesInFlight());

    for (size_t i = 0; i < swapChain.framesInFlight(); ++i) {
        uniformBuffers.push_back(
                device.createBuffer(
                        sizeof(UniformBufferObject),
                        BufferUsageFlags::Uniform,
                        MemoryUsage::CpuToGpu
                )
        );
    }

    Texture exampleTexture = createTexture(device, "img.png");
    TextureView exampleTextureView = device.createTextureView(
            exampleTexture,
            TextureViewType::Type2D,
            PixelFormat::RGBA8Unorm_srgb,
            TextureAspect::ColorOnly
    );
    Sampler exampleSampler = device.createSampler(
            SamplerDescriptor(
                    SamplerFilter::Nearest,
                    SamplerFilter::Nearest,
                    SamplerAddressMode::Repeat,
                    SamplerAddressMode::Repeat,
                    SamplerAddressMode::Repeat
            )
    );

    // Create the bind group entries for each uniform buffer and the one texture sampler
    std::vector<std::vector<BindGroupEntry>> uboTextureBindGroupEntries;
    uboTextureBindGroupEntries.reserve(uniformBuffers.size());

    for (auto& uniformBuffer : uniformBuffers) {
        uboTextureBindGroupEntries.emplace_back(
                std::vector{
                        BindGroupEntry(uniformBuffer, 0, sizeof(UniformBufferObject)),
                        BindGroupEntry(exampleSampler, exampleTextureView, TextureLayout::ShaderReadOnly)
                }
        );
    }

    // Create the final bind groups we will actually reference in a render pass
    std::vector<BindGroup> uboTextureBindGroups = device.createBindGroups(
            uboBindGroupLayout,
            uboTextureBindGroupEntries
    );

    while (!window->getShouldClose()) {
        Window::pollEvents();

        auto currentFrameIndex = swapChain.nextFrameIndex();
        updateUniformBuffer(uniformBuffers[currentFrameIndex], window->getWidth(), window->getHeight());
        device.waitForFence(inFlightFences[currentFrameIndex]);
        auto currentFramebuffer = swapChain.getFramebuffer(
                currentFrameIndex,
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
                    uboBindGroupLayout,
                    renderPipelineLayout,
                    renderPipeline,
                    renderCommandQueue
            );
            continue;
        }

        auto currentCommandBuffer = renderCommandQueue.getCommandBuffer(currentFrameIndex);
        auto currentCommandEncoder = currentCommandBuffer.beginCommandEncoding();
        auto currentRenderPassEncoder = currentCommandEncoder.beginRenderPass(
                renderPassAttachment,
                currentFramebuffer,
                Rect2D(
                        0, 0,
                        window->getWidth(), window->getHeight()
                ),
                ClearColorValue(0, 0, 0, 1)
        );

        currentRenderPassEncoder.setPipeline(renderPipeline);
        currentRenderPassEncoder.setVertexBuffer(0, vertexBuffer);
        currentRenderPassEncoder.setIndexBuffer(indexBuffer, IndexType::Uint16);
        currentRenderPassEncoder.setBindGroup(renderPipelineLayout, uboTextureBindGroups[currentFrameIndex]);
        currentRenderPassEncoder.drawIndexed(indices.size());

        currentRenderPassEncoder.endRenderPass();
        currentCommandEncoder.endCommandEncoding();

        device.resetFence(inFlightFences[currentFrameIndex]);

        renderCommandQueue.submit(
                imageAvailableSemaphores[currentFrameIndex],
                PipelineStage::ColorAttachment,
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
                    uboBindGroupLayout,
                    renderPipelineLayout,
                    renderPipeline,
                    renderCommandQueue
            );
        }
    }

    // Let everything finish on the device before exiting...
    device.waitIdle();

    return 0;
}
