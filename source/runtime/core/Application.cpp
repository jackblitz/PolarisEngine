#include "Application.h"
#include <iostream>
#include <stdexcept>
#include <SDL3/SDL.h>
#include "Logger.h"
//#include "/rendering/VideoRenderer.h"

namespace polaris {
    /**
     * @brief Constructs an Application object.
     * Initializes the application with a null window pointer and logs the construction.
     */
    Application::Application() : m_window(nullptr) {
        LOG_INFO("Application constructed");
    }

    /**
     * @brief Destroys the Application object.
     * Logs the destruction of the application.
     */
    Application::~Application() {
        LOG_INFO("Application destructed");
    }

    /**
     * @brief Initializes the application.
     * This method sets up the engine and prepares the application for running.
     * It also handles potential exceptions during engine initialization.
     */
    void Application::initialize() {
        LOG_INFO("Application initializing...");
        try {
            m_engine.setApplication(this);
            m_engine.initialize();
        } catch (const std::exception& e) {
            LOG_ERROR("Application initialization failed");
            throw;
        }
    }

    /**
     * @brief Runs the main application loop.
     * This method delegates to the engine's run method to start the event loop.
     */
    void Application::run() {
        LOG_INFO("Application Running...");
        m_engine.run();
    }

    /**
     * @brief Sets the SDL window for the application.
     * This method is called by the Engine once the window has been created.
     * It also calls the OnCreated virtual method.
     * @param window A pointer to the SDL_Window object. Must not be null.
     */
    void Application::setWindow(SDL_Window* window) {
        if (!window) {
            LOG_ERROR("Cannot set null window");
            throw std::invalid_argument("Cannot set null window");
        }

        m_window = window;
        OnCreated();

        SDL_ShowWindow(m_window);
    }

    /**
     * @brief Called when the application's window is created and ready.
     * This is a virtual method that can be overridden by derived classes
     * to perform application-specific initialization once the window is available.
     * It logs the event.
     */
    void Application::OnCreated() {
        LOG_INFO("Application OnCreated: Window is now available.");
    }

    /**
     * @brief Called by the Engine before shutdown.
     * This is a virtual method that can be overridden by derived classes
     * to perform application-specific cleanup before the engine shuts down.
     * It logs the event.
     */
    void Application::onDestroy() {
        LOG_INFO("Application onDestroy: Cleaning up application resources.");
    }


    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    /*                                                       */
    /* Remove this source, and replace with your SDL sources */
    /*                                                       */
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
} // namespace polaris