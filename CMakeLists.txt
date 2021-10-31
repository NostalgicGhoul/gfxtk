cmake_minimum_required(VERSION 3.20)
project(gfxtk)

set(CMAKE_CXX_STANDARD 17)

option(GFXTK_GENERATE_METAL_SHADERS "Generate Metal shaders for all provided shader sources" ON)
option(GFXTK_VERBOSE_LOGGING "Enabled to log _all_ Vulkan validation layer messages (this can be slow on some systems)" OFF)

set(GFXTK_GRAPHICS_BACKEND "vulkan")
set(GFXTK_GIT_INFO_HEADER_PATH ${CMAKE_SOURCE_DIR}/libs/gfxtk_logging/src/gfxtk/)
include(cmake/GitInfo.cmake)
include(cmake/ConfigureBackends.cmake)
include(cmake/Shaders.cmake)

add_subdirectory(libs/glm)

add_subdirectory(libs/gfxtk_core)
add_subdirectory(libs/gfxtk_logging)
add_subdirectory(libs/${GFXTK_WINDOW_BACKEND_LIBS})
add_subdirectory(libs/${GFXTK_GRAPHICS_BACKEND_LIB_NAME})

# Include examples...
add_subdirectory(examples/00-triangle)
add_subdirectory(examples/01-uniform-buffers)

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
        src/gfxtk/BindGroupEntry.cpp src/gfxtk/BindGroupEntry.hpp src/gfxtk/Sampler.cpp src/gfxtk/Sampler.hpp)

target_compile_definitions(gfxtk PRIVATE GFXTK_BUILD_LIBRARY=1)

target_include_directories(gfxtk INTERFACE src)

target_link_libraries(gfxtk
        ${GFXTK_GRAPHICS_BACKEND_LIBS}
        gfxtk_logging
        ${GFXTK_WINDOW_BACKEND_LIBS}
        glm
)

add_dependencies(gfxtk gfxtk_git_info)
