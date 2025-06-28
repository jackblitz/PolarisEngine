//
// Created by luke on 6/23/2025.
//

#include "PlatformRenderer.h"


PlatformRenderer* PlatformRenderer::_instance = nullptr;

PlatformRenderer::PlatformRenderer() {

}

PlatformRenderer::~PlatformRenderer() {
}

void PlatformRenderer::RenderFrame() {

}

void PlatformRenderer::CreateRenderer(SDL_Window *window) {
    _instance = new PlatformRenderer();
}



PlatformRenderer * PlatformRenderer::getInstance() {
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