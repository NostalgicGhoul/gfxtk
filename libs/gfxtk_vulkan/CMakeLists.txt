cmake_minimum_required(VERSION 3.20)
project(gfxtk_vulkan)

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

add_library(gfxtk_vulkan STATIC
        src/gfxtk/backend/vulkan/Device.cpp
        src/gfxtk/backend/vulkan/Device.hpp
)

target_include_directories(gfxtk_vulkan INTERFACE src)

target_link_libraries(gfxtk_vulkan
        Vulkan::Vulkan
)
