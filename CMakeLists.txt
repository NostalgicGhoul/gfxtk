cmake_minimum_required(VERSION 3.20)
project(gfxtk)

set(CMAKE_CXX_STANDARD 17)

include(cmake/ConfigureBackends.cmake)
include(cmake/Shaders.cmake)

add_subdirectory(libs/glm)

add_subdirectory(libs/gfxtk_core)
add_subdirectory(libs/gfxtk_logging)
add_subdirectory(libs/${GFXTK_WINDOW_BACKEND_LIBS})
add_subdirectory(libs/${GFXTK_GRAPHICS_BACKEND_LIBS})

# Include examples...
add_subdirectory(examples/00-triangle)

# For some dumbass reason I have to include this even though I have `target_include_directories(gfxtk INTERFACE src)`
# which works perfectly with every other referenced project. Whatever.
include_directories(src)

add_library(gfxtk SHARED
        src/gfxtk/BindGroup.cpp
        src/gfxtk/BindGroup.hpp
        src/gfxtk/BindGroupLayout.cpp
        src/gfxtk/BindGroupLayout.hpp
        src/gfxtk/Buffer.cpp
        src/gfxtk/Buffer.hpp
        src/gfxtk/CommandBuffer.cpp
        src/gfxtk/CommandBuffer.hpp
        src/gfxtk/CommandEncoder.cpp
        src/gfxtk/CommandEncoder.hpp
        src/gfxtk/CommandQueue.cpp
        src/gfxtk/CommandQueue.hpp
        src/gfxtk/Device.cpp
        src/gfxtk/Device.hpp
        src/gfxtk/Fence.cpp
        src/gfxtk/Fence.hpp
        src/gfxtk/Framebuffer.cpp
        src/gfxtk/Framebuffer.hpp
        src/gfxtk/ImageCopyBuffer.cpp
        src/gfxtk/ImageCopyBuffer.hpp
        src/gfxtk/ImageCopyTexture.cpp
        src/gfxtk/ImageCopyTexture.hpp
        src/gfxtk/Instance.cpp
        src/gfxtk/Instance.hpp
        src/gfxtk/Pipeline.cpp
        src/gfxtk/Pipeline.hpp
        src/gfxtk/PipelineLayout.cpp
        src/gfxtk/PipelineLayout.hpp
        src/gfxtk/RenderPassAttachment.cpp
        src/gfxtk/RenderPassAttachment.hpp
        src/gfxtk/RenderPassEncoder.cpp
        src/gfxtk/RenderPassEncoder.hpp
        src/gfxtk/RenderPipelineDescriptor.cpp
        src/gfxtk/RenderPipelineDescriptor.hpp
        src/gfxtk/Semaphore.cpp
        src/gfxtk/Semaphore.hpp
        src/gfxtk/Shader.cpp
        src/gfxtk/Shader.hpp
        src/gfxtk/ShaderLibrary.cpp
        src/gfxtk/ShaderLibrary.hpp
        src/gfxtk/SwapChain.cpp
        src/gfxtk/SwapChain.hpp
        src/gfxtk/SwapChainConfig.cpp
        src/gfxtk/SwapChainConfig.hpp
        src/gfxtk/Texture.cpp
        src/gfxtk/Texture.hpp
        src/gfxtk/TextureView.cpp
        src/gfxtk/TextureView.hpp
        src/gfxtk/Window.cpp
        src/gfxtk/Window.hpp
)

target_include_directories(gfxtk INTERFACE src)

target_link_libraries(gfxtk
        gfxtk_logging
        ${GFXTK_GRAPHICS_BACKEND_LIBS}
        ${GFXTK_WINDOW_BACKEND_LIBS}
        glm
)
