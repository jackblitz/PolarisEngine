#!/bin/bash

# Build SDL3 and SDL3_image libraries for Android
# This script builds the shared libraries and copies them to the correct location

set -e

# Default values
if [ -z "$ANDROID_NDK" ]; then
    if [ -d "$ANDROID_HOME/ndk/29.0.13113456" ]; then
        ANDROID_NDK="$ANDROID_HOME/ndk/29.0.13113456"
    elif [ -d "$ANDROID_HOME/ndk/27.0.12077973" ]; then
        ANDROID_NDK="$ANDROID_HOME/ndk/27.0.12077973"
    elif [ -d "$ANDROID_HOME/ndk/25.2.9519653" ]; then
        ANDROID_NDK="$ANDROID_HOME/ndk/25.2.9519653"
    else
        echo "Error: Android NDK not found. Please set ANDROID_NDK environment variable."
        exit 1
    fi
fi
ANDROID_ABI=${ANDROID_ABI:-"arm64-v8a"}
ANDROID_PLATFORM=${ANDROID_PLATFORM:-"android-21"}
BUILD_DIR="build-android"
CMAKE_VERSION="3.30.3"

echo "Building SDL3 and SDL3_image for Android"
echo "NDK: $ANDROID_NDK"
echo "ABI: $ANDROID_ABI"
echo "Platform: $ANDROID_PLATFORM"
echo "Build directory: $BUILD_DIR"
echo ""
echo "This will build SDL3 and SDL3_image as shared libraries for Android"
echo "and copy them to $BUILD_DIR/android-libs/$ANDROID_ABI/"
echo ""

# Check if NDK exists
if [ ! -d "$ANDROID_NDK" ]; then
    echo "Error: Android NDK not found at $ANDROID_NDK"
    echo "Please set ANDROID_NDK environment variable or install NDK"
    exit 1
fi

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake" \
    -DANDROID_ABI="$ANDROID_ABI" \
    -DANDROID_PLATFORM="$ANDROID_PLATFORM" \
    -DANDROID_STL=c++_static \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_ANDROID_NDK="$ANDROID_NDK"

# Build
cmake --build . --parallel

echo "Build completed successfully!"
echo "Libraries are available in: $BUILD_DIR/android-libs/$ANDROID_ABI/"
echo "Files:"
ls -la "android-libs/$ANDROID_ABI/" 