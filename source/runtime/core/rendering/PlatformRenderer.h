//
// Created by luke on 6/23/2025.
//

#ifndef PLATFORMRENDERING_H
#define PLATFORMRENDERING_H
#include <SDL3/SDL.h>

/**
 * @brief Abstract base class for platform-specific rendering.
 *
 * This class defines the interface for rendering operations that are specific to a particular platform
 * or rendering API (e.g., SDL, OpenGL, DirectX). Concrete subclasses will implement these methods
 * to provide actual rendering capabilities.
 */
class PlatformRenderer {
    public:
    /**
     * @brief Constructs a PlatformRenderer object.
     */
    PlatformRenderer();

    /**
     * @brief Destroys the PlatformRenderer object.
     */
    virtual ~PlatformRenderer();

    /**
     * @brief Renders a single frame.
     *
     * This pure virtual function must be implemented by subclasses to perform the actual rendering
     * operations for a frame.
     */
    virtual void RenderFrame();

    /**
     * @brief Creates the renderer for the given window.
     * @param window A pointer to the SDL_Window to associate the renderer with.
     *
     * This pure virtual function must be implemented by subclasses to initialize and create
     * the platform-specific renderer.
     */
    virtual void CreateRenderer(SDL_Window* window);

    /**
     * @brief Gets the singleton instance of the PlatformRenderer.
     * @return A pointer to the singleton PlatformRenderer instance.
     */
    static PlatformRenderer* getInstance();

protected:
    /**
     * @brief The singleton instance of the PlatformRenderer.
     */
    static PlatformRenderer* _instance;

};

#endif //PLATFORMRENDERING_H
