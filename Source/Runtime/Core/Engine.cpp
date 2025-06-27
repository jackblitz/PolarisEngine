#include "Engine.h"
#include "Application.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace polaris {

Engine::Engine() : m_window(nullptr), m_application(nullptr) {

}

Engine::~Engine() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
    SDL_Quit();
    std::cout << "Engine destructed and SDL cleaned up." << std::endl;
}

void Engine::setApplication(Application* app) {
    m_application = app;
}

void Engine::initialize() {
    std::cout << "Engine initialized." << std::endl;
    /*( if (m_application) {
         m_application->initialize();
     }*/
    std::cout << "Attempting to initialize SDL3..." << std::endl;

    // Initialize SDL3
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Create SDL window (hidden initially)
    m_window = SDL_CreateWindow(
        "Vega42 - SDL3 + Vulkan",
        800, 600,
        SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN
    );
    if (!m_window) {
        std::cerr << "Failed to create SDL3 window: " << SDL_GetError() << std::endl;
    } else {
        // Only call setWindow if application is set
        if (m_application) {
            m_application->setWindow(m_window);
        } else {
            std::cout << "Window created but no application set to receive it." << std::endl;
        }
    }
}

void Engine::run() {
    std::cout << "Engine running..." << std::endl;

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                quit = true;
            }
        }

        //Call rendering engine
    }
}

} // namespace polaris 