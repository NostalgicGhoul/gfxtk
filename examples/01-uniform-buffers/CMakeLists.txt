cmake_minimum_required(VERSION 3.20)
project(example01_uniform_buffers)

set(CMAKE_CXX_STANDARD 17)

add_gfxtk_shader_library(
        TARGET example01_uniform_buffers_shaders
        OUTPUT shaders/
        SHADERS shader.vert shader.frag
)

add_executable(example01_uniform_buffers
        uniform_buffers.cpp
        UniformBufferObject.cpp
        UniformBufferObject.hpp
        Vertex.cpp
        Vertex.hpp
)

target_link_libraries(example01_uniform_buffers
        gfxtk
        example01_uniform_buffers_shaders
)
