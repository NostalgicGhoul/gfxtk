# NOTE: Vulkan is always a requirement for `gfxtk` due to our use of `glslc` for shaders (among other shader tools)
#       the plan is to use Vulkan's variant of GLSL, compile to Spir-V, then use Vulkan's transpilation tool to convert
#       the Spir-V to the shader language of each supported backend.
find_package(Vulkan REQUIRED COMPONENTS glslangValidator spirv-cross)
find_program(glslangValidator NAMES glslangValidator HINTS Vulkan::glslangValidator)
find_program(spirv-cross NAMES spirv-cross HINTS Vulkan::spirv-cross)

function(add_gfxtk_shader_library)
    set(one_value_args TARGET OUTPUT)
    set(multi_value_args SHADERS)
    cmake_parse_arguments(ARG "" "${one_value_args}" "${multi_value_args}" ${ARGN})

    if(GFXTK_SOURCE_DIR STREQUAL "")
        get_target_property(GFXTK_SOURCE_DIR gfxtk SOURCE_DIR)
    endif()

    get_filename_component(ABSOLUTE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${ARG_OUTPUT}" ABSOLUTE)
    set(ABSOLUTE_STAGING_DIR "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${ARG_OUTPUT}")

    add_custom_command(OUTPUT ${ABSOLUTE_OUTPUT_DIR} ${ABSOLUTE_STAGING_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${ABSOLUTE_OUTPUT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${ABSOLUTE_STAGING_DIR}"
            COMMENT "Creating shader library directory ${ARG_OUTPUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    set(GFXTK_SHADER_LIBRARIES "")

    # First things first, we generate all SPIR-V files from the shader sources
    foreach(source_file_path IN ITEMS ${ARG_SHADERS})
        set(INPUT_FILE ${CMAKE_CURRENT_LIST_DIR}/${source_file_path})

        if(NOT EXISTS ${INPUT_FILE})
            message(FATAL_ERROR "shader ${source_file_path} was not found!")
        endif()

        get_filename_component(FILENAME ${INPUT_FILE} NAME)
        get_filename_component(SHADER_TYPE ${INPUT_FILE} LAST_EXT)

        set(OUTPUT_FILE ${ABSOLUTE_OUTPUT_DIR}/${FILENAME}.spv)

        add_custom_command(OUTPUT ${OUTPUT_FILE}
                COMMAND ${glslangValidator} --quiet -V ${INPUT_FILE} -o ${OUTPUT_FILE}
                MAIN_DEPENDENCY ${INPUT_FILE}
                DEPENDS ${ABSOLUTE_STAGING_DIR}
                COMMENT "Compiling SPIR-V shader for ${source_file_path}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

        list(APPEND GFXTK_SHADER_LIBRARIES ${OUTPUT_FILE})

        if (GFXTK_GENERATE_METAL_SHADERS)
            set(OUTPUT_METAL_SHADER_LIBRARY_FILE ${ABSOLUTE_OUTPUT_DIR}/${FILENAME}.metal)

            add_custom_command(OUTPUT ${OUTPUT_METAL_SHADER_LIBRARY_FILE}
                    COMMAND ${spirv-cross} --msl ${OUTPUT_FILE} --output ${OUTPUT_METAL_SHADER_LIBRARY_FILE}
                    MAIN_DEPENDENCY ${OUTPUT_FILE}
                    DEPENDS ${ABSOLUTE_OUTPUT_DIR} ${OUTPUT_FILE}
                    COMMENT "Generating Metal shader for ${source_file_path}"
                    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            )

            list(APPEND GFXTK_SHADER_LIBRARIES ${OUTPUT_METAL_SHADER_LIBRARY_FILE})
        endif()
    endforeach()

    set(FAKE_CPP_FILE ${ABSOLUTE_STAGING_DIR}/shader_empty.cpp)
    configure_file(${GFXTK_SOURCE_DIR}/cmake/assets/shader_empty.cpp.in ${FAKE_CPP_FILE})

    add_library(${ARG_TARGET} STATIC
            ${FAKE_CPP_FILE}
            ${GFXTK_SHADER_LIBRARIES}
    )
endfunction(add_gfxtk_shader_library)
