cmake_minimum_required(VERSION 3.30)
project(PolarisEngine)


set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party)
set(INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/packages)

# Build SDL3
add_subdirectory(${THIRD_PARTY_DIR}/sdl)

if(ANDROID)
    add_library(PolarisEngine SHARED
            source/runtime/core/Engine.cpp
            source/runtime/core/Application.cpp
            source/runtime/core/Logger.cpp
            source/runtime/core/rendering/PlatformRenderer.cpp
            source/runtime/core/rendering/SDLRenderer.cpp

    )
    set(PLATFORM_COMPILE_OPTIONS
            -DANDROID
            #-DVK_USE_PLATFORM_ANDROID_KHR     # Vulkan Android-specific platform define
            -fno-limit-debug-info             # Debug info for Android
            -std=c++14                        # Use C++14 for Android (adjust as needed)
    )
    #target_compile_definitions(PolarisEngine PRIVATE PLATFORM_ANDROID)
    find_library(
            # Sets the name of the path variable.
            log-lib

            # Specifies the name of the NDK library that
            # you want CMake to locate.
            log )


    target_link_libraries(PolarisEngine PUBLIC PolarisEngine_Headers SDL3::SDL3 android ${log-lib})
else()
    add_library(PolarisEngine STATIC
            source/runtime/core/Logger.cpp
            source/runtime/core/rendering/PlatformRenderer.cpp
            source/runtime/core/rendering/SDLRenderer.cpp
            source/runtime/core/Engine.cpp
            source/runtime/core/Application.cpp
    )
    #set_target_properties(PolarisEngine PROPERTIES
    #    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    #    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    #    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    #)
    find_package(Vulkan REQUIRED)
    #target_compile_definitions(PolarisEngine PRIVATE PLATFORM_WINDOWS _USE_MATH_DEFINES VK_USE_PLATFORM_WIN32_KHR)
    target_link_libraries(PolarisEngine PUBLIC PolarisEngine_Headers SDL3::SDL3 Vulkan::Vulkan)
endif()

if(WIN32)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_WINDOWS _USE_MATH_DEFINES VK_USE_PLATFORM_WIN32_KHR)
elseif(UNIX) # This will cover Linux
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_LINUX SDL_RENDER_WAYLAND) # Enable Wayland rendering for Linux
elseif(APPLE)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_MAC SDL_RENDER_METAL) # Enable Metal rendering for macOS/iOS
elseif(ANDROID)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_ANDROID) # Add any other macOS-specific definitions if needed
endif()

target_include_directories(PolarisEngine PRIVATE
        ${Vulkan_INCLUDE_DIRS}
        ${THIRD_PARTY_DIR}/SDL/include
        #${THIRD_PARTY_DIR}/SDL_image/include
        #  ${FFMPEG_INCLUDE_DIR}
)


# Interface target for headers
add_library(PolarisEngine_Headers INTERFACE)
target_include_directories(PolarisEngine_Headers INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core
       # ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core/rendering
       # ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core/video
)