# First, we configure information on the target system. Currently, we have the following targets with specific
# configurations:
#  - Windows
#      * GLFW [Default window]
#      * Vulkan [Default graphics]
#      * DX12 [Alternative graphics]
#  - MacOS
#      * GLFW [Default window]
#      * Metal [Default graphics]
#      * Vulkan [Alternative graphics]
#  - Linux
#      * GLFW [Default window]
#      * Vulkan [Default graphics]
#  - iOS
#      * [Undecided window]
#      * Metal [Default graphics]
#      * Vulkan [Alternative graphics]
#  - Android
#      * [Undecided window]
#      * Vulkan [Default graphics]
# TODO: Of the major operating systems, we still need to add support for Android.
if (APPLE)
    # NOTE: On `macOS` we default to using `GLFW` as the windowing library, unlike iOS which GLFW doesn't work on.
    if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
        set(GFXTK_TARGET_OS iOS)
    else()
        set(GFXTK_TARGET_OS macOS)
    endif()
elseif (UNIX)
    # NOTE: This makes no effort to tell the difference between Linux, *BSD, or any other *nix OSes.
    set(GFXTK_TARGET_OS Linux)
    # I'm not entirely sure why this is required now on Linux :shrug:
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
elseif (MSVC OR MSYS OR MINGW)
    set(GFXTK_TARGET_OS Windows)
endif()

# Next, we configure the backends that will be compiled while accounting for overrides of the defaults
if(APPLE)
    if(GFXTK_TARGET_OS STREQUAL "macOS")
        add_definitions(-DGFXTK_TARGET_OS_MACOS)

        if(DEFINED GFXTK_WINDOW_BACKEND)
            if(NOT GFXTK_WINDOW_BACKEND STREQUAL "glfw")
                message(FATAL_ERROR "gfxtk only supports window backend `glfw` on macOS! (${GFXTK_WINDOW_BACKEND} is not supported)")
            endif()
        else()
            set(GFXTK_WINDOW_BACKEND "glfw")
        endif()

        if(DEFINED GFXTK_GRAPHICS_BACKEND)
            if(NOT (GFXTK_GRAPHICS_BACKEND STREQUAL "vulkan" OR GFXTK_GRAPHICS_BACKEND STREQUAL "metal"))
                message(FATAL_ERROR "gfxtk only supports graphics backends `vulkan` and `metal` on macOS! (${GFXTK_GRAPHICS_BACKEND} is not supported)")
            endif()
        else()
            set(GFXTK_GRAPHICS_BACKEND "metal")
        endif()
    else()
        # Assume iOS... iOS, WatchOS, tvOS and all other Apple OSes usually will use the same iOS methods.
        add_definitions(-DGFXTK_TARGET_OS_IOS)
        message(FATAL_ERROR "gfxtk currently does not support iOS (support is coming once the Metal backend is done)")
    endif()
elseif(GFXTK_TARGET_OS STREQUAL "Linux")
    add_definitions(-DGFXTK_TARGET_OS_LINUX)

    if(DEFINED GFXTK_WINDOW_BACKEND)
        if(NOT GFXTK_WINDOW_BACKEND STREQUAL "glfw")
            message(FATAL_ERROR "gfxtk only supports window backend `glfw` on Linux! (${GFXTK_WINDOW_BACKEND} is not supported)")
        endif()
    else()
        set(GFXTK_WINDOW_BACKEND "glfw")
    endif()

    if(DEFINED GFXTK_GRAPHICS_BACKEND)
        if(NOT GFXTK_GRAPHICS_BACKEND STREQUAL "vulkan")
            message(FATAL_ERROR "gfxtk only supports graphics backend `vulkan` on Linux! (${GFXTK_GRAPHICS_BACKEND} is not supported)")
        endif()
    else()
        set(GFXTK_GRAPHICS_BACKEND "vulkan")
    endif()
elseif(GFXTK_TARGET_OS STREQUAL "Android")
    add_definitions(-DGFXTK_TARGET_OS_ANDROID)
    message(FATAL_ERROR "gfxtk currently does not support Android (support coming once iOS support is finished)")
elseif(GFXTK_TARGET_OS STREQUAL "Windows")
    add_definitions(-DGFXTK_TARGET_OS_WINDOWS)
    if(DEFINED GFXTK_GRAPHICS_BACKEND)
        if(NOT GFXTK_GRAPHICS_BACKEND STREQUAL "vulkan")
            message(FATAL_ERROR "gfxtk only supports window backend `glfw` on Windows! (${GFXTK_WINDOW_BACKEND} is not supported)")
        endif()
    else()
        set(GFXTK_WINDOW_BACKEND "glfw")
    endif()

    if(DEFINED GFXTK_GRAPHICS_BACKEND)
        if(NOT (GFXTK_GRAPHICS_BACKEND STREQUAL "vulkan" OR GFXTK_GRAPHICS_BACKEND STREQUAL "dx12"))
            message(FATAL_ERROR "gfxtk only supports graphics backends `vulkan` and `dx12` on Windows! (${GFXTK_GRAPHICS_BACKEND} is not supported)")
        endif()
    else()
        # NOTE: I don't like DirectX because of Microsoft's history with it. That is the only reason I default to
        #       Vulkan. I'm not going to pretend it's because of the (very real) better performance that Vulkan
        #       _sometimes_ offers over DX12. Yes, I also realize I'm hypocritical for making `Metal` the default on
        #       Apple systems since there is Vulkan support on them too. ¯\_(ツ)_/¯
        set(GFXTK_GRAPHICS_BACKEND "vulkan")
    endif()
else()
    message(FATAL_ERROR "gfxtk does not support operating system `${GFXTK_TARGET_OS}`!")
endif()

# Finally, we set the backend "libs" variable for anything that wants to load the libs in
# We also create easy to use C-defines for the backends such as `GFXTK_WINDOW_BACKEND_GLFW` and
# `GFXTK_GRAPHICS_BACKEND_VULKAN`
if(GFXTK_WINDOW_BACKEND STREQUAL "glfw")
    set(GFXTK_WINDOW_BACKEND_LIBS "gfxtk_glfw")
    add_definitions(-DGFXTK_WINDOW_BACKEND_GLFW=1)
else()
    message(FATAL_ERROR "unknown window backend `${GFXTK_WINDOW_BACKEND}`!")
endif()

if(GFXTK_GRAPHICS_BACKEND STREQUAL "vulkan")
    set(GFXTK_GRAPHICS_BACKEND_LIB_NAME "gfxtk_vulkan")
    set(GFXTK_GRAPHICS_BACKEND_LIBS "gfxtk_vulkan")
    add_definitions(-DGFXTK_GRAPHICS_BACKEND_VULKAN=1)
elseif(GFXTK_GRAPHICS_BACKEND STREQUAL "metal")
    set(GFXTK_GRAPHICS_BACKEND_LIB_NAME "gfxtk_metal")
    set(GFXTK_GRAPHICS_BACKEND_LIBS "gfxtk_metal" "-framework AppKit" "-framework QuartzCore" "-framework Metal")
    add_definitions(-DGFXTK_GRAPHICS_BACKEND_METAL=1)
else()
    message(FATAL_ERROR "unknown graphics backend `${GFXTK_GRAPHICS_BACKEND}`!")
endif()
