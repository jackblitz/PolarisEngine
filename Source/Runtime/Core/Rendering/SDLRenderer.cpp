#include "SDLRenderer.h"

#include <PlatformRenderer.h>
#include <stdexcept>

namespace polaris
{
       /* m_pSdlRenderer = SDL_CreateRenderer(m_pWindow, nullptr);
        if (m_pSdlRenderer == nullptr)
        {
            throw std::runtime_error("Failed to create SDL3 renderer");
        }*/

    /**
     * @brief Constructs an SDLRenderer object.
     */
    SDLRenderer::SDLRenderer(): m_pSdlRenderer(nullptr) {

    }

    /**
     * @brief Destroys the SDLRenderer object.
     */
    SDLRenderer::~SDLRenderer()
    {
        SDL_DestroyRenderer(m_pSdlRenderer);
        SDL_Quit();
    }

    /**
     * @brief Creates an SDL renderer for the given window.
     * @param window A pointer to the SDL_Window to associate the renderer with.
     * @throws std::runtime_error if the SDL renderer cannot be created.
     */
    void SDLRenderer::CreateRenderer(SDL_Window* window) {
        m_pSdlRenderer = SDL_CreateRenderer(window, nullptr);
        if (m_pSdlRenderer == nullptr)
        {
            throw std::runtime_error("Failed to create SDL3 renderer");
        }
    }


    /**
     * @brief Renders a single frame using SDL.
     *
     * This method clears the renderer with a red color, and then presents the renderer.
     */
    void SDLRenderer::RenderFrame()
    {
        SDL_SetRenderDrawColor(m_pSdlRenderer, 255, 0, 0, 255);
        SDL_RenderClear(m_pSdlRenderer);
        SDL_RenderPresent(m_pSdlRenderer);
    }
}