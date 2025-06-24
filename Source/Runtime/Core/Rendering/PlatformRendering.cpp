//
// Created by luke on 6/23/2025.
//

#include "PlatformRendering.h"


PlatformRendering* PlatformRendering::_instance = nullptr;

PlatformRendering::PlatformRendering() {

}

PlatformRendering::~PlatformRendering() {
}

PlatformRendering * PlatformRendering::getInstance() {
/*#ifdef PLATFORM_ANDROID
    if (!_instance) {
        instance_ = new PlatformAndroid();
    }
#elif defined(PLATFORM_WINDOWS)
    if (!_instance) {
        instance_ = new PlatformWindows();
    }
#else
#endif*/
    return _instance;
}