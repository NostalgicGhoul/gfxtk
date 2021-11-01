cmake_minimum_required(VERSION 3.20)
project(example02_textures)

set(CMAKE_CXX_STANDARD 17)

add_gfxtk_shader_library(
        TARGET example02_textures_shaders
        OUTPUT shaders/
        SHADERS shader.vert shader.frag
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/img.png
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_LIST_DIR}/img.png" "${CMAKE_CURRENT_BINARY_DIR}/img.png"
        MAIN_DEPENDENCY ${CMAKE_CURRENT_LIST_DIR}/img.png
        COMMENT "Copying prebuilt asset img.png to ${CMAKE_CURRENT_BINARY_DIR}/img.png"
)

add_executable(example02_textures
        stb_image.c
        stb_image.h
        textures.cpp
        UniformBufferObject.cpp
        UniformBufferObject.hpp
        Vertex.cpp
        Vertex.hpp

        img.png
)

target_link_libraries(example02_textures
        gfxtk
        example02_textures_shaders
)
