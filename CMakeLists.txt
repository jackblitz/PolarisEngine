cmake_minimum_required(VERSION 3.30)
project(PolarisEngine)

set(CMAKE_CXX_STANDARD 20)

# Set paths for third-party libraries
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party)
#set(INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/packages)

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

# Find Vulkan
find_package(Vulkan REQUIRED)

# FFmpeg configuration
set(FFMPEG_DIR ${THIRD_PARTY_DIR}/ffmpeg)
set(FFMPEG_INCLUDE_DIR ${FFMPEG_DIR}/libavcodec ${FFMPEG_DIR}/libavformat ${FFMPEG_DIR}/libavutil ${FFMPEG_DIR}/libswscale ${FFMPEG_DIR}/libswresample)

# Create the static library
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
)

# Set output directories for the static library
set_target_properties(PolarisEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

if(WIN32)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_WINDOWS _USE_MATH_DEFINES VK_USE_PLATFORM_WIN32_KHR)
elseif(APPLE)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_MAC)
elseif(UNIX AND NOT ANDROID)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_LINUX)
elseif(ANDROID)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_ANDROID)
endif()

# Link SDL3, Vulkan, and FFmpeg
target_link_libraries(PolarisEngine PUBLIC PolarisEngine_Headers SDL3::SDL3 SDL3_image::SDL3_image Vulkan::Vulkan)

target_include_directories(PolarisEngine PRIVATE 
    ${THIRD_PARTY_DIR}/SDL/include 
    ${THIRD_PARTY_DIR}/SDL_image/include
)

# Interface target for headers
add_library(PolarisEngine_Headers INTERFACE)
target_include_directories(PolarisEngine_Headers INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core
    ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core/rendering
    ${CMAKE_CURRENT_SOURCE_DIR}/source/runtime/core/video
)