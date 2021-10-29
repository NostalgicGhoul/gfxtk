cmake_minimum_required(VERSION 3.20)
project(example_triangle)

set(CMAKE_CXX_STANDARD 17)

add_gfxtk_shader_library(
        TARGET example_triangle_shaders
        OUTPUT shaders/
        SHADERS shader.vert shader.frag
)

add_executable(example_triangle
        triangle.cpp
        Vertex.cpp
        Vertex.hpp
)

target_link_libraries(example_triangle
        gfxtk
        example_triangle_shaders
)
