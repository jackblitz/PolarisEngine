#include "Engine.h"
#include "Application.h"
#include "Logger.h"
#include <SDL3/SDL.h>
#include <stdexcept>

namespace polaris {

Engine::Engine() : m_window(nullptr), m_application(nullptr) {
    LOG_INFO("Engine constructed");
    // Constructor is now lightweight - initialization moved to initialize()
}

Engine::~Engine() {
    //shutdown();
    LOG_INFO("Engine destructed");
}

void Engine::setApplication(Application* app) {
    m_application = app;
    LOG_DEBUG("Application set on Engine");
}

void Engine::initialize() {
    LOG_INFO("Engine initializing...");
    
    // Initialize SDL3 with better error handling
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_ERROR("SDL initialization failed: " + std::string(SDL_GetError()));
        throw std::runtime_error("SDL initialization failed: " + std::string(SDL_GetError()));
    }
    
    // Create window with better error handling
    m_window = SDL_CreateWindow(
        "Vega42 - SDL3 + Vulkan",
        800, 600,
        SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE
    );
    
    if (!m_window) {
        LOG_ERROR("Window creation failed: " + std::string(SDL_GetError()));
        SDL_Quit();
        throw std::runtime_error("Window creation failed: " + std::string(SDL_GetError()));
    }
    
    LOG_INFO("Engine initialized successfully");
    
    // Notify application if set
    if (m_application) {
        m_application->setWindow(m_window);
    } else {
        LOG_WARN("No application set, skipping setWindow call");
    }
}

void Engine::run() {
    if (!m_window) {
        LOG_ERROR("Cannot run engine: window not initialized");
        throw std::runtime_error("Cannot run engine: window not initialized");
    }
    
    LOG_INFO("Engine running...");
    
    SDL_Event event;
    bool quit = false;
    
    // Show window after initialization
    SDL_ShowWindow(m_window);
    
    while (!quit) {
        // Process all pending events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    LOG_INFO("Quit event received");
                    quit = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    LOG_DEBUG("Key pressed, quitting");
                    quit = true;
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    LOG_DEBUG("Window resized");
                    break;
            }
        }
        
        // Render frame (placeholder for rendering engine)
        // renderFrame();
        
        // Cap frame rate to ~60 FPS
        SDL_Delay(16);
    }

    shutdown();
}

void Engine::shutdown() {
    LOG_INFO("Engine shutting down...");
    
    // Notify application before cleanup
    if (m_application) {
        m_application->onDestroy();
    } else {
        LOG_WARN("No application set, skipping onDestroy call");
    }
    
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    
    SDL_Quit();
    LOG_INFO("Engine shutdown complete");
}

} // namespace polaris 