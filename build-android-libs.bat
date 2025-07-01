@echo off
REM Build SDL3 and SDL3_image libraries for Android
REM This script builds the shared libraries and copies them to the correct location

setlocal enabledelayedexpansion

REM Default values
set ANDROID_NDK=C:\Program Files (x86)\Android\AndroidNDK\android-ndk-r23c
echo Debug: ANDROID_NDK is %ANDROID_NDK%
if "%ANDROID_ABI%"=="" set ANDROID_ABI=arm64-v8a
if "%ANDROID_PLATFORM%"=="" set ANDROID_PLATFORM=android-24
set BUILD_DIR=build-android
set CMAKE_VERSION=3.30.3

echo Building SDL3 and SDL3_image for Android
echo NDK: %ANDROID_NDK%
echo ABI: %ANDROID_ABI%
echo Platform: %ANDROID_PLATFORM%
echo Build directory: %BUILD_DIR%
echo.
echo This will build SDL3 and SDL3_image as shared libraries for Android
echo and copy them to %BUILD_DIR%\android-libs\%ANDROID_ABI%\
echo.

REM Check if NDK exists
if not exist "%ANDROID_NDK%" (
    echo Error: Android NDK not found at %ANDROID_NDK%
    echo Please set ANDROID_NDK environment variable or install NDK
    exit /b 1
)

REM Create build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM Configure with CMake
cmake .. ^
    -DCMAKE_TOOLCHAIN_FILE="%ANDROID_NDK%\build\cmake\android.toolchain.cmake" ^
    -DANDROID_ABI="%ANDROID_ABI%" ^
    -DANDROID_PLATFORM="%ANDROID_PLATFORM%" ^
    -DANDROID_STL=c++_static ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_ANDROID_NDK="%ANDROID_NDK%"

if errorlevel 1 (
    echo CMake configuration failed
    exit /b 1
)

REM Build
cmake --build . --parallel

if errorlevel 1 (
    echo Build failed
    exit /b 1
)

echo Build completed successfully!
echo Libraries are available in: %BUILD_DIR%\android-libs\%ANDROID_ABI%\
echo Files:
dir "android-libs\%ANDROID_ABI%\"

pause 