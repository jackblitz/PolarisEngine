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

    SDLRenderer::SDLRenderer(): m_pSdlRenderer(nullptr) {

    }

    SDLRenderer::~SDLRenderer()
    {
        SDL_DestroyRenderer(m_pSdlRenderer);
        SDL_Quit();
    }

    void SDLRenderer::CreateRenderer(SDL_Window* window) {
        m_pSdlRenderer = SDL_CreateRenderer(window, nullptr);
        if (m_pSdlRenderer == nullptr)
        {
            throw std::runtime_error("Failed to create SDL3 renderer");
        }
    }


    void SDLRenderer::RenderFrame()
    {
        SDL_SetRenderDrawColor(m_pSdlRenderer, 255, 0, 0, 255);
        SDL_RenderClear(m_pSdlRenderer);
        SDL_RenderPresent(m_pSdlRenderer);
    }
}