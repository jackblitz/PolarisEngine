#include "Engine.h"

#include <SDLRenderer.h>

#include "Application.h"
#include "Logger.h"
#include <SDL3/SDL.h>
#include <stdexcept>

namespace polaris {
    /**
     * @brief Constructs an Engine object.
     * Initializes internal pointers to null and logs the construction.
     * The constructor is kept lightweight; actual initialization is done in initialize().
     */
    Engine::Engine() : m_application(nullptr) {
        LOG_INFO("Engine constructed");
        // Constructor is now lightweight - initialization moved to initialize()
    }

    /**
     * @brief Destroys the Engine object.
     * Logs the destruction of the engine. Actual SDL cleanup is handled in the shutdown() method.
     */
    Engine::~Engine() {
        LOG_INFO("Engine destructed");
    }

    /**
     * @brief Sets the application instance for the engine.
     * This allows the engine to communicate with the application, particularly for window events.
     * @param app A pointer to the Application instance.
     */
    void Engine::setApplication(Application* app) {
        m_application = app;
        LOG_DEBUG("Application set on Engine");
    }

    /**
     * @brief Initializes the engine.
     * This method initializes SDL, creates the application window, and sets up the application instance.
     * It also handles error logging and throws exceptions if SDL or window creation fails.
     */
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

        m_renderer = new SDLRenderer();

        // Notify application if set
        if (m_application) {
            m_application->setWindow(m_window);
        } else {
            LOG_WARN("No application set, skipping setWindow call");
        }

        m_renderer->CreateRenderer(m_window);
    }

    /**
     * @brief Runs the main engine loop.
     * This method handles SDL events and keeps the engine running until a quit event is received.
     * It also ensures the window is shown and includes a basic frame rate cap.
     * @throws std::runtime_error if the window is not initialized before calling run.
     */
    void Engine::run() {
        if (!m_window) {
            LOG_ERROR("Cannot run engine: window not initialized");
            throw std::runtime_error("Cannot run engine: window not initialized");
        }

        LOG_INFO("Engine running...");

        SDL_Event event;
        bool quit = false;

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
            m_renderer->RenderFrame();

            // Cap frame rate to ~60 FPS
            SDL_Delay(16);
        }

        shutdown();
    }

    /**
     * @brief Shuts down the engine and cleans up resources.
     * This method notifies the application of destruction, destroys the SDL window, and quits SDL subsystems.
     */
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