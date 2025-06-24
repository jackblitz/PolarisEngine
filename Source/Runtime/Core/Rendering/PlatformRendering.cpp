//
// Created by luke on 6/23/2025.
//

#include "PlatformRendering.h"


PlatformRendering* PlatformRendering::instance_ = nullptr;

PlatformRendering::PlatformRendering() {

}

PlatformRendering::~PlatformRendering() {
}

PlatformRendering * PlatformRendering::getInstance() {
#ifdef PLATFORM_ANDROID
    if (!instance_) {
        instance_ = new PlatformAndroid();
    }
#elif defined(PLATFORM_WINDOWS)
    if (!instance_) {
        instance_ = new PlatformWindows();
    }
#else
#endif
    return instance_;
}