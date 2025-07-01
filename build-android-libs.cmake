cmake_minimum_required(VERSION 3.30)
project(AndroidSDL3Libs)

# Set paths for third-party libraries
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party)

# Set Android-specific options for SDL3
set(SDL_SHARED ON CACHE BOOL "Build shared library" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Build static library" FORCE)
set(SDL_STATIC_PIC OFF CACHE BOOL "Build static library with PIC" FORCE)

# Set Android-specific options for SDL3_image
set(SDL_IMAGE_SHARED ON CACHE BOOL "Build shared library" FORCE)
set(SDL_IMAGE_STATIC OFF CACHE BOOL "Build static library" FORCE)

# Build SDL3
add_subdirectory(${THIRD_PARTY_DIR}/SDL)

# Build SDL3_image (depends on SDL3)
add_subdirectory(${THIRD_PARTY_DIR}/SDL_image)

# Create output directory
add_custom_target(create_output_dir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}
    COMMENT "Creating output directory for Android libraries"
)

# Copy SDL3 library
add_custom_target(copy_sdl3 ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:SDL3::SDL3>
        ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}/libSDL3.so
    COMMENT "Copying libSDL3.so to ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}"
)

# Copy SDL3_image library
add_custom_target(copy_sdl3_image ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:SDL3_image::SDL3_image>
        ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}/libSDL3_image.so
    COMMENT "Copying libSDL3_image.so to ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}"
)

# Copy Polaris library
add_custom_target(copy_polaris ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:Polaris>
        ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}/libPolaris.so
    COMMENT "Copying libPolaris.so to ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}"
)

# Set dependencies
add_dependencies(copy_sdl3 create_output_dir SDL3::SDL3)
add_dependencies(copy_sdl3_image create_output_dir SDL3_image::SDL3_image)
add_dependencies(copy_polaris create_output_dir Polaris)

# Print information about the build
message(STATUS "Building Android libraries for ABI: ${ANDROID_ABI}")
message(STATUS "Output directory: ${CMAKE_BINARY_DIR}/android-libs/${ANDROID_ABI}") 