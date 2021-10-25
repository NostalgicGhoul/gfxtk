# NOTE: Vulkan is always a requirement for `gfxtk` due to our use of `glslc` for shaders (among other shader tools)
#       the plan is to use Vulkan's variant of GLSL, compile to Spir-V, then use Vulkan's transpilation tool to convert
#       the Spir-V to the shader language of each supported backend.
find_package(Vulkan REQUIRED COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

# Create a new shader library which can be referenced through `target_link_libraries(library_target_name)`
#
# Usage:
#     add_gfxtk_shader_library(library_target_name output_directory shaderFile...)
function(add_gfxtk_shader_library library_target_name output_directory)
    get_filename_component(ABSOLUTE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${output_directory}" ABSOLUTE)

    add_custom_command(OUTPUT ${ABSOLUTE_OUTPUT_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${ABSOLUTE_OUTPUT_DIR}"
            COMMENT "Creating shader library directory ${output_directory}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    set(GFXTK_SHADER_SOURCES "")

    foreach(source_file_path IN ITEMS ${ARGN})
        set(INPUT_FILE ${CMAKE_CURRENT_LIST_DIR}/${source_file_path})

        if(NOT EXISTS ${INPUT_FILE})
            message(FATAL_ERROR "shader ${source_file_path} was not found!")
        endif()

        get_filename_component(FILENAME ${INPUT_FILE} NAME)

        set(OUTPUT_FILE ${ABSOLUTE_OUTPUT_DIR}/${FILENAME}.spv)

        add_custom_command(OUTPUT ${OUTPUT_FILE}
                COMMAND ${glslc_executable} ${INPUT_FILE} -o ${OUTPUT_FILE}
                MAIN_DEPENDENCY ${INPUT_FILE}
                DEPENDS ${ABSOLUTE_OUTPUT_DIR}
                COMMENT "Compiling shader ${source_file_path}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

        list(APPEND GFXTK_SHADER_SOURCES ${INPUT_FILE})
    endforeach()

    set(FAKE_CPP_FILE ${ABSOLUTE_OUTPUT_DIR}/shader_empty.cpp)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/assets/shader_empty.cpp.in ${FAKE_CPP_FILE})

    add_library(${library_target_name} STATIC
            ${FAKE_CPP_FILE}
            ${GFXTK_SHADER_SOURCES}
    )
endfunction(add_gfxtk_shader_library)
