cmake_minimum_required(VERSION 3.30)
project(PolarisEngine)

set(CMAKE_CXX_STANDARD 20)

# Set paths for third-party libraries
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party)
set(INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/packages)

# Build SDL3
add_subdirectory(${THIRD_PARTY_DIR}/SDL)

# Build SDL3_image (depends on SDL3)
#Diable Dav!d and enable aom for AV1 decoding
#set(SDL_IMAGE_AVIF OFF CACHE BOOL "Disable AVIF support in SDL_image" FORCE)
add_subdirectory(${THIRD_PARTY_DIR}/SDL_image)

# Build SDL3_mixer (depends on SDL3)
add_subdirectory(${THIRD_PARTY_DIR}/SDL_mixer)

set(SDLTTF_VENDORED TRUE CACHE BOOL "Use vendored third-party libraries" FORCE)

# Build SDL3_ttf (depends on SDL3 and FreeType)
add_subdirectory(${THIRD_PARTY_DIR}/SDL_ttf)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Create the shared library
add_library(PolarisEngine SHARED
    library.cpp
        source/runtime/core/rendering/PlatformRendering.cpp
)

# Platform-specific compile definitions and options
if(WIN32)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_WINDOWS _USE_MATH_DEFINES VK_USE_PLATFORM_WIN32_KHR)
    target_link_libraries(PolarisEngine PUBLIC Vulkan::Vulkan)
elseif(APPLE)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_MAC)

elseif(UNIX AND NOT ANDROID)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_LINUX)
elseif(ANDROID)
    target_compile_definitions(PolarisEngine PRIVATE PLATFORM_ANDROID)
endif()

# Link SDL3 and headers
target_link_libraries(PolarisEngine PUBLIC PolarisEngine_Headers SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer)

# Set output directories
#set_target_properties(PolarisEngine PROPERTIES
#    OUTPUT_NAME "engine"
#    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/cmake-debug-build
#    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
#    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
#)

# Interface target for headers
add_library(PolarisEngine_Headers INTERFACE)
target_include_directories(PolarisEngine_Headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
