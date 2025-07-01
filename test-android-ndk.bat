@echo off
REM Test Android NDK setup

echo Testing Android NDK setup...
echo.

REM Check for NDK installations
echo Checking for Android NDK installations:

if exist "%ANDROID_HOME%\ndk\29.0.13113456" (
    echo Found NDK 29.0.13113456 at: %ANDROID_HOME%\ndk\29.0.13113456
    set TEST_NDK=%ANDROID_HOME%\ndk\29.0.13113456
) else if exist "%ANDROID_HOME%\ndk\27.0.12077973" (
    echo Found NDK 27.0.12077973 at: %ANDROID_HOME%\ndk\27.0.12077973
    set TEST_NDK=%ANDROID_HOME%\ndk\27.0.12077973
) else if exist "%ANDROID_HOME%\ndk\25.2.9519653" (
    echo Found NDK 25.2.9519653 at: %ANDROID_HOME%\ndk\25.2.9519653
    set TEST_NDK=%ANDROID_HOME%\ndk\25.2.9519653
) else if exist "C:\Program Files (x86)\Android\AndroidNDK\android-ndk-r23c" (
    echo Found NDK r23c at: "C:\Program Files (x86)\Android\AndroidNDK\android-ndk-r23c"
    set "TEST_NDK=C:\Program Files (x86)\Android\AndroidNDK\android-ndk-r23c"
) else (
    echo No NDK found in common locations
    echo Please install Android NDK or set ANDROID_NDK environment variable
    pause
    exit /b 1
)

echo.
echo Testing NDK toolchain at: %TEST_NDK%
echo.

REM Check if toolchain file exists
if not exist "%TEST_NDK%\build\cmake\android.toolchain.cmake" (
    echo ERROR: Toolchain file not found at %TEST_NDK%\build\cmake\android.toolchain.cmake
    pause
    exit /b 1
)

echo Toolchain file found: %TEST_NDK%\build\cmake\android.toolchain.cmake

REM Check if sysroot exists
if not exist "%TEST_NDK%\toolchains\llvm\prebuilt\windows-x86_64\sysroot" (
    echo ERROR: Sysroot not found at %TEST_NDK%\toolchains\llvm\prebuilt\windows-x86_64\sysroot
    pause
    exit /b 1
)

echo Sysroot found: %TEST_NDK%\toolchains\llvm\prebuilt\windows-x86_64\sysroot

REM Check if clang exists
if not exist "%TEST_NDK%\toolchains\llvm\prebuilt\windows-x86_64\bin\clang.exe" (
    echo ERROR: Clang not found at %TEST_NDK%\toolchains\llvm\prebuilt\windows-x86_64\bin\clang.exe
    pause
    exit /b 1
)

echo Clang found: %TEST_NDK%\toolchains\llvm\prebuilt\windows-x86_64\bin\clang.exe

echo.
echo NDK setup appears to be correct!
echo You can now run: build-android-libs.bat
echo.
pause 