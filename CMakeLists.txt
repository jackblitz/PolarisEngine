cmake_minimum_required(VERSION 3.30)
project(PolarisEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fix MinGW compilation issues
#if(MINGW)
#    add_compile_definitions(_WIN32_WINNT=0x0601)
#    add_compile_options(-D_WIN32_WINNT=0x0601)
#endif()

# Set paths for third-party libraries
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party)
set(INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/packages)

message(STATUS "Path to third-party libs: ${THIRD_PARTY_DIR}")
# Build SDL3
add_subdirectory(${THIRD_PARTY_DIR}/SDL)

# Build SDL3_image (depends on SDL3)
#Diable Dav!d and enable aom for AV1 decoding
#set(SDL_IMAGE_AVIF OFF CACHE BOOL "Disable AVIF support in SDL_image" FORCE)
add_subdirectory(${THIRD_PARTY_DIR}/SDL_image)


# Build SDL3_mixer (depends on SDL3)
#add_subdirectory(${THIRD_PARTY_DIR}/SDL_mixer)

#set(SDLTTF_VENDORED TRUE CACHE BOOL "Use vendored third-party libraries" FORCE)

# Build SDL3_ttf (depends on SDL3 and FreeType)
#add_subdirectory(${THIRD_PARTY_DIR}/SDL_ttf)

#set(DAV1D_ASM OFF CACHE BOOL "Disable dav1d assembly optimizations" FORCE)


# FFmpeg configuration
#set(FFMPEG_DIR ${THIRD_PARTY_DIR}/ffmpeg)
#set(FFMPEG_INCLUDE_DIR ${FFMPEG_DIR}/libavcodec ${FFMPEG_DIR}/libavformat ${FFMPEG_DIR}/libavutil ${FFMPEG_DIR}/libswscale ${FFMPEG_DIR}/libswresample)

# Build FFmpeg libraries - commented out for now
#add_subdirectory(${FFMPEG_DIR}/libavutil)
#add_subdirectory(${FFMPEG_DIR}/libavcodec)
#add_subdirectory(${FFMPEG_DIR}/libavformat)
#add_subdirectory(${FFMPEG_DIR}/libswscale)
# add_subdirectory(${FFMPEG_DIR}/libswresample)

if(ANDROID)
    add_library(PolarisEngine SHARED
        library.cpp
        source/runtime/core/Engine.cpp
        source/runtime/core/Application.cpp
        source/runtime/core/Logger.cpp
        source/runtime/core/rendering/PlatformRenderer.cpp
        source/runtime/core/rendering/SDLRenderer.cpp
      # source/runtime/core/rendering/VulkanRenderer.cpp
        source/runtime/core/rendering/VideoRenderer.cpp
        source/runtime/core/video/VideoDecoder.cpp
        source/runtime/core/video/FFmpegVideoDecoder.cpp
        source/runtime/core/video/VideoDecoderFactory.cpp
    )
    set(PLATFORM_COMPILE_OPTIONS
            -DANDROID
            #-DVK_USE_PLATFORM_ANDROID_KHR     # Vulkan Android-specific platform define
            -fno-limit-debug-info             # Debug info for Android
            -std=c++14                        # Use C++14 for Android (adjust as needed)
    )
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_ANDROID)
    find_library(
            # Sets the name of the path variable.
            log-lib

            # Specifies the name of the NDK library that
            # you want CMake to locate.
            log )


    target_link_libraries(PolarisEngine PUBLIC PolarisEngine_Headers SDL3::SDL3 SDL3_image::SDL3_image android ${log-lib})
else()
    add_library(PolarisEngine STATIC
        library.cpp
        source/runtime/core/Engine.cpp
        source/runtime/core/Application.cpp
        source/runtime/core/Logger.cpp
        source/runtime/core/rendering/PlatformRenderer.cpp
        source/runtime/core/rendering/SDLRenderer.cpp
        source/runtime/core/rendering/VulkanRenderer.cpp
        source/runtime/core/rendering/VideoRenderer.cpp
        source/runtime/core/video/VideoDecoder.cpp
        source/runtime/core/video/FFmpegVideoDecoder.cpp
        source/runtime/core/video/VideoDecoderFactory.cpp
    )
    #set_target_properties(PolarisEngine PROPERTIES
    #    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    #    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    #    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    #)
    find_package(Vulkan REQUIRED)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_WINDOWS _USE_MATH_DEFINES VK_USE_PLATFORM_WIN32_KHR)
    target_link_libraries(PolarisEngine PUBLIC PolarisEngine_Headers SDL3::SDL3 SDL3_image::SDL3_image Vulkan::Vulkan)
endif()


    target_include_directories(PolarisEngine PRIVATE
        ${Vulkan_INCLUDE_DIRS}
        ${THIRD_PARTY_DIR}/SDL/include
        ${THIRD_PARTY_DIR}/SDL_image/include
      #  ${FFMPEG_INCLUDE_DIR}
    )


# Interface target for headers
add_library(PolarisEngine_Headers INTERFACE)
target_include_directories(PolarisEngine_Headers INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core
    ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core/rendering
    ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core/video
)