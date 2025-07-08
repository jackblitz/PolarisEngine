#pragma once

#include "PlatformRenderer.h"
#include <SDL3/SDL.h>

namespace polaris
{
    /**
 * @brief Implements a renderer using SDL's rendering capabilities.
 *
 * This class inherits from PlatformRenderer and provides concrete implementations
 * for creating an SDL renderer and rendering frames using SDL.
 */
    class SDLRenderer: public PlatformRenderer
    {
    public:
        /**
         * @brief Constructs an SDLRenderer object.
         */
        SDLRenderer();
        /**
         * @brief Destroys the SDLRenderer object.
         */
        ~SDLRenderer();

        /**
         * @brief Creates an SDL renderer for the given window.
         * @param window A pointer to the SDL_Window to associate the renderer with.
         */
        void CreateRenderer(SDL_Window* window) override;
        /**
         * @brief Renders a single frame using SDL.
         */
        void RenderFrame() override;

    private:
        /**
         * @brief Pointer to the SDL_Renderer instance.
         */
        SDL_Renderer* m_pSdlRenderer;
    };
}