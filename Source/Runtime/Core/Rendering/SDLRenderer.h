#pragma once

#include <PlatformRenderer.h>
#include <SDL3/SDL.h>
#include "VulkanRenderer.h"

namespace polaris
{
    class SDLRenderer: public PlatformRenderer
    {
    public:
        SDLRenderer();
        ~SDLRenderer();

        void CreateRenderer(SDL_Window* window) override;
        void RenderFrame() override;

    private:
        SDL_Renderer* m_pSdlRenderer;
    };
}