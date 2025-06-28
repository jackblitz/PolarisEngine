//
// Created by luke on 6/23/2025.
//

#include "PlatformRenderer.h"


PlatformRenderer* PlatformRenderer::_instance = nullptr;

/**
 * @brief Constructs a PlatformRenderer object.
 */
PlatformRenderer::PlatformRenderer() {

}

/**
 * @brief Destroys the PlatformRenderer object.
 */
PlatformRenderer::~PlatformRenderer() {
}

/**
 * @brief Renders a single frame.
 *
 * This is a placeholder implementation for the base class. Subclasses should override this
 * to provide actual rendering logic.
 */
void PlatformRenderer::RenderFrame() {

}

/**
 * @brief Creates the renderer for the given window.
 * @param window A pointer to the SDL_Window to associate the renderer with.
 *
 * This is a placeholder implementation for the base class. Subclasses should override this
 * to initialize and create the platform-specific renderer.
 */
void PlatformRenderer::CreateRenderer(SDL_Window *window) {
    _instance = new PlatformRenderer();
}



/**
 * @brief Gets the singleton instance of the PlatformRenderer.
 * @return A pointer to the singleton PlatformRenderer instance.
 */
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