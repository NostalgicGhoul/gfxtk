cmake_minimum_required(VERSION 3.20)
project(gfxtk_logging)

set(CMAKE_CXX_STANDARD 17)

add_library(gfxtk_logging STATIC
        src/gfxtk/log.cpp
        src/gfxtk/log.hpp
)

target_include_directories(gfxtk_logging INTERFACE src)

target_compile_definitions(gfxtk_logging PRIVATE GFXTK_BUILD_LIBRARY=1)

target_link_libraries(gfxtk_logging
        gfxtk_core
)
