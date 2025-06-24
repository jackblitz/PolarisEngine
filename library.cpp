#include "library.h"
#include <SDL3/SDL.h>
#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;

    SDLState state = {};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
    }

    state.window = SDL_CreateWindow("SDL_WINDOW", 800, 600,0);


    bool isRunning = true;

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    isRunning = false;
            }
        }
    }


    //cleanup(state);
}

void cleanup(SDLState &state) {
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}