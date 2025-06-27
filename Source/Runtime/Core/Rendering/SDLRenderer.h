#pragma once

#include <SDL3/SDL.h>
#include "VulkanRenderer.h"

namespace polaris
{
    class SDLRenderer
    {
    public:
        SDLRenderer();
        ~SDLRenderer();

        void render();

    private:
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pSdlRenderer;
    };
}