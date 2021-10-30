cmake_minimum_required(VERSION 3.20)
project(gfxtk_vulkan)

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

add_subdirectory(libs/VulkanMemoryAllocator)

add_library(gfxtk_vulkan STATIC
        src/gfxtk/backend/vulkan/BindGroupLayout.cpp
        src/gfxtk/backend/vulkan/BindGroupLayout.hpp
        src/gfxtk/backend/vulkan/BlendFactor.cpp
        src/gfxtk/backend/vulkan/BlendFactor.hpp
        src/gfxtk/backend/vulkan/BlendOp.cpp
        src/gfxtk/backend/vulkan/BlendOp.hpp
        src/gfxtk/backend/vulkan/Buffer.cpp
        src/gfxtk/backend/vulkan/Buffer.hpp
        src/gfxtk/backend/vulkan/BufferUsageFlags.cpp
        src/gfxtk/backend/vulkan/BufferUsageFlags.hpp
        src/gfxtk/backend/vulkan/ColorSpace.cpp
        src/gfxtk/backend/vulkan/ColorSpace.hpp
        src/gfxtk/backend/vulkan/ColorWriteMask.cpp
        src/gfxtk/backend/vulkan/ColorWriteMask.hpp
        src/gfxtk/backend/vulkan/CommandBuffer.cpp
        src/gfxtk/backend/vulkan/CommandBuffer.hpp
        src/gfxtk/backend/vulkan/CommandEncoder.cpp
        src/gfxtk/backend/vulkan/CommandEncoder.hpp
        src/gfxtk/backend/vulkan/CommandQueue.cpp
        src/gfxtk/backend/vulkan/CommandQueue.hpp
        src/gfxtk/backend/vulkan/CompareOp.cpp
        src/gfxtk/backend/vulkan/CompareOp.hpp
        src/gfxtk/backend/vulkan/CullMode.cpp
        src/gfxtk/backend/vulkan/CullMode.hpp
        src/gfxtk/backend/vulkan/Device.cpp
        src/gfxtk/backend/vulkan/Device.hpp
        src/gfxtk/backend/vulkan/Fence.cpp
        src/gfxtk/backend/vulkan/Fence.hpp
        src/gfxtk/backend/vulkan/Framebuffer.cpp
        src/gfxtk/backend/vulkan/Framebuffer.hpp
        src/gfxtk/backend/vulkan/IndexType.cpp
        src/gfxtk/backend/vulkan/IndexType.hpp
        src/gfxtk/backend/vulkan/Instance.cpp
        src/gfxtk/backend/vulkan/Instance.hpp
        src/gfxtk/backend/vulkan/LoadOp.cpp
        src/gfxtk/backend/vulkan/LoadOp.hpp
        src/gfxtk/backend/vulkan/MemoryUsage.cpp
        src/gfxtk/backend/vulkan/MemoryUsage.hpp
        src/gfxtk/backend/vulkan/Pipeline.cpp
        src/gfxtk/backend/vulkan/Pipeline.hpp
        src/gfxtk/backend/vulkan/PipelineLayout.cpp
        src/gfxtk/backend/vulkan/PipelineLayout.hpp
        src/gfxtk/backend/vulkan/PipelineStage.cpp
        src/gfxtk/backend/vulkan/PipelineStage.hpp
        src/gfxtk/backend/vulkan/PixelFormat.cpp
        src/gfxtk/backend/vulkan/PixelFormat.hpp
        src/gfxtk/backend/vulkan/PrimitiveTopology.cpp
        src/gfxtk/backend/vulkan/PrimitiveTopology.hpp
        src/gfxtk/backend/vulkan/RenderPassAttachment.cpp
        src/gfxtk/backend/vulkan/RenderPassAttachment.hpp
        src/gfxtk/backend/vulkan/RenderPassEncoder.cpp
        src/gfxtk/backend/vulkan/RenderPassEncoder.hpp
        src/gfxtk/backend/vulkan/SampleCount.cpp
        src/gfxtk/backend/vulkan/SampleCount.hpp
        src/gfxtk/backend/vulkan/Semaphore.cpp
        src/gfxtk/backend/vulkan/Semaphore.hpp
        src/gfxtk/backend/vulkan/Shader.cpp
        src/gfxtk/backend/vulkan/Shader.hpp
        src/gfxtk/backend/vulkan/ShaderStageFlags.cpp
        src/gfxtk/backend/vulkan/ShaderStageFlags.hpp
        src/gfxtk/backend/vulkan/StencilOp.cpp
        src/gfxtk/backend/vulkan/StencilOp.hpp
        src/gfxtk/backend/vulkan/StoreOp.cpp
        src/gfxtk/backend/vulkan/StoreOp.hpp
        src/gfxtk/backend/vulkan/SwapChain.cpp
        src/gfxtk/backend/vulkan/SwapChain.hpp
        src/gfxtk/backend/vulkan/SwapChainConfig.cpp
        src/gfxtk/backend/vulkan/SwapChainConfig.hpp
        src/gfxtk/backend/vulkan/Texture.cpp
        src/gfxtk/backend/vulkan/Texture.hpp
        src/gfxtk/backend/vulkan/TextureLayout.cpp
        src/gfxtk/backend/vulkan/TextureLayout.hpp
        src/gfxtk/backend/vulkan/TriangleFillMode.cpp
        src/gfxtk/backend/vulkan/TriangleFillMode.hpp
        src/gfxtk/backend/vulkan/VertexFormat.cpp
        src/gfxtk/backend/vulkan/VertexFormat.hpp
)

target_include_directories(gfxtk_vulkan INTERFACE src)

target_compile_definitions(gfxtk_vulkan PRIVATE GFXTK_BUILD_LIBRARY=1)

target_link_libraries(gfxtk_vulkan
        Vulkan::Vulkan
        VulkanMemoryAllocator
        gfxtk_core
        gfxtk_logging
        ${GFXTK_WINDOW_BACKEND_LIBS}
)
