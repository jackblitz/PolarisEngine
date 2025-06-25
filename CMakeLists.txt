cmake_minimum_required(VERSION 3.30)
project(PolarisEngine)

set(CMAKE_CXX_STANDARD 20)

# Find Vulkan and SDL3 (installed by install.bat)
find_package(Vulkan REQUIRED)
find_package(SDL3 REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/Packages") #If not found run install.bat
find_package(SDL3_image REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/Packages")
find_package(SDL3_mixer REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/Packages")
find_package(SDL3_ttf REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/Packages")

# Create the shared library
add_library(PolarisEngine SHARED
    library.cpp
    Source/Runtime/Core/Rendering/PlatformRendering.cpp
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
set_target_properties(PolarisEngine PROPERTIES
    OUTPUT_NAME "engine"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/debug
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/debug
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/debug
)

# Interface target for headers
add_library(PolarisEngine_Headers INTERFACE)
target_include_directories(PolarisEngine_Headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy SDL3.dll to output directory after build
add_custom_command(TARGET PolarisEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/Packages/bin/SDL3.dll"
        $<TARGET_FILE_DIR:PolarisEngine>
)

add_custom_command(TARGET PolarisEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/Packages/bin/SDL3_image.dll"
        $<TARGET_FILE_DIR:PolarisEngine>
)

add_custom_command(TARGET PolarisEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/Packages/bin/SDL3_mixer.dll"
        $<TARGET_FILE_DIR:PolarisEngine>
)

add_custom_command(TARGET PolarisEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/Packages/bin/SDL3_ttf.dll"
        $<TARGET_FILE_DIR:PolarisEngine>
)