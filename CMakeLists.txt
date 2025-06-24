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

add_library(PolarisEngine SHARED library.cpp
        Source/Runtime/Core/Rendering/PlatformRendering.h
        Source/Runtime/Core/Rendering/PlatformRendering.cpp)
