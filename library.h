#ifndef POLARISENGINE_LIBRARY_H
#define POLARISENGINE_LIBRARY_H
#include <SDL3/SDL.h>


struct SDLState {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

void hello();

void cleanup(SDLState *state);
#endif //POLARISENGINE_LIBRARY_H