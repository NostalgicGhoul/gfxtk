cmake_minimum_required(VERSION 3.20)
project(gfxtk)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/glm)

add_subdirectory(libs/gfxtk_glfw)
add_subdirectory(libs/gfxtk_vulkan)

# For some dumbass reason I have to include this even though I have `target_include_directories(gfxtk INTERFACE src)`
# which works perfectly with every other referenced project. Whatever.
include_directories(src)

add_executable(gfxtk
        src/main.cpp
        src/gfxtk/Device.cpp
        src/gfxtk/Device.hpp
        src/gfxtk/Window.cpp
        src/gfxtk/Window.hpp
)

target_include_directories(gfxtk INTERFACE src)

target_link_libraries(gfxtk
        gfxtk_vulkan
        gfxtk_glfw
        glm
)
