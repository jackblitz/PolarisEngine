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

# Set the library name to engine.dll
set_target_properties(PolarisEngine PROPERTIES
        OUTPUT_NAME "engine"
)

# Create an interface target for the headers
add_library(PolarisEngine_Headers INTERFACE)
target_include_directories(PolarisEngine_Headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Make the main library include the headers
target_link_libraries(PolarisEngine PUBLIC PolarisEngine_Headers)

add_library(PolarisEngine SHARED library.cpp
        Source/Runtime/Core/Rendering/PlatformRendering.h
        Source/Runtime/Core/Rendering/PlatformRendering.cpp)
