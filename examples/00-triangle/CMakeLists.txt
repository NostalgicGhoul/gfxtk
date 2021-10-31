cmake_minimum_required(VERSION 3.20)
project(example00_triangle)

set(CMAKE_CXX_STANDARD 17)

add_gfxtk_shader_library(
        TARGET example00_triangle_shaders
        OUTPUT shaders/
        SHADERS shader.vert shader.frag
)

add_executable(example00_triangle
        triangle.cpp
        Vertex.cpp
        Vertex.hpp
)

target_link_libraries(example00_triangle
        gfxtk
        example00_triangle_shaders
)
