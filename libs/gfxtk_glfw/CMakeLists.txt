cmake_minimum_required(VERSION 3.20)
project(gfxtk_glfw)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/glfw)

add_library(gfxtk_glfw STATIC
        src/gfxtk/backend/glfw/Window.cpp
        src/gfxtk/backend/glfw/Window.hpp
)

target_include_directories(gfxtk_glfw INTERFACE src)

target_link_libraries(gfxtk_glfw
        glfw
)
