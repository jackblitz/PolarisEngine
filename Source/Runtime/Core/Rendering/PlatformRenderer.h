//
// Created by luke on 6/23/2025.
//

#ifndef PLATFORMRENDERING_H
#define PLATFORMRENDERING_H
#include <SDL3/SDL.h>

class PlatformRenderer {
    public:
    PlatformRenderer();

    virtual ~PlatformRenderer();
    virtual void RenderFrame();
    virtual void CreateRenderer(SDL_Window* window);
    static PlatformRenderer* getInstance();

protected:
    static PlatformRenderer* _instance;

};

#endif //PLATFORMRENDERING_H
