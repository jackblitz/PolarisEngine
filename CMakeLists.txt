cmake_minimum_required(VERSION 3.30)
project(workspace)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DPLATFORM_MAC)
elseif(UNIX AND NOT ANDROID)
    add_definitions(-DPLATFORM_LINUX)
elseif(ANDROID)
    add_definitions(-DPLATFORM_ANDROID)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/$<CONFIG>/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/$<CONFIG>/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/$<CONFIG>/)

# Build projects
add_subdirectory(polaris)

add_subdirectory(vega42)
