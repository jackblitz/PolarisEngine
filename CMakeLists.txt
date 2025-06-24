add_subdirectory(${CMAKE_SOURCE_DIR}/lib/engine/Source/Third_Party/SDL ${CMAKE_BINARY_DIR}/lib/engine/Source/Third_Party/SDL)

cmake_minimum_required(VERSION 3.30)
project(PolarisEngine)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DPLATFORM_MAC)
elseif(UNIX AND NOT ANDROID)
    add_definitions(-DPLATFORM_LINUX)
elseif(ANDROID)
    add_definitions(-DPLATFORM_ANDROID)
endif()

# Create the shared library
add_library(PolarisEngine SHARED library.cpp
        Source/Runtime/Core/Rendering/PlatformRendering.cpp)

target_link_libraries(PolarisEngine
    PUBLIC
        SDL3::SDL3
        SDL3_Image
        SDL3_Mixer
        SDL3_ttf
        PolarisEngine_Headers
)

# Set the library name to engine.dll and output directories
set_target_properties(PolarisEngine PROPERTIES
    OUTPUT_NAME "engine"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/out/release
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/debug
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/out/release
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/debug
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/out/release
)

# Create an interface target for the headers
add_library(PolarisEngine_Headers INTERFACE)
target_include_directories(PolarisEngine_Headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
