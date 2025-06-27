#include "SDLRenderer.h"
#include <stdexcept>

namespace polaris
{
    SDLRenderer::SDLRenderer() : m_pWindow(nullptr), m_pSdlRenderer(nullptr)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error("Failed to initialize SDL3");
        }

        m_pWindow = SDL_CreateWindow("Vega42", 1280, 720, 0);
        if (m_pWindow == nullptr)
        {
            throw std::runtime_error("Failed to create SDL3 window");
        }

        m_pSdlRenderer = SDL_CreateRenderer(m_pWindow, nullptr);
        if (m_pSdlRenderer == nullptr)
        {
            throw std::runtime_error("Failed to create SDL3 renderer");
        }
    }

    SDLRenderer::~SDLRenderer()
    {
        SDL_DestroyRenderer(m_pSdlRenderer);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
    }

    void SDLRenderer::render()
    {
        SDL_SetRenderDrawColor(m_pSdlRenderer, 255, 0, 0, 255);
        SDL_RenderClear(m_pSdlRenderer);
        SDL_RenderPresent(m_pSdlRenderer);
    }
}