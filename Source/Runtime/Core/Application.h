#ifndef POLARIS_APPLICATION_H
#define POLARIS_APPLICATION_H

#include "Engine.h"
#include <SDL3/SDL.h>

namespace polaris {

class Application {
public:
    /**
     * @brief Constructs an Application object.
     * Initializes the application with a null window pointer.
     */
    Application();

    /**
     * @brief Destroys the Application object.
     * Cleans up any resources held by the application.
     */
    virtual ~Application();

    /**
     * @brief Initializes the application.
     * This method sets up the engine and prepares the application for running.
     */
    virtual void initialize();

    /**
     * @brief Runs the main application loop.
     * This method delegates to the engine's run method to start the event loop.
     */
    void run();

    /**
     * @brief Sets the SDL window for the application.
     * This method is called by the Engine once the window has been created.
     * @param window A pointer to the SDL_Window object.
     */
    void setWindow(SDL_Window* window);

    /**
     * @brief Called when the application's window is created and ready.
     * This is a virtual method that can be overridden by derived classes
     * to perform application-specific initialization once the window is available.
     */
    virtual void OnCreated();

    /**
     * @brief Called by the Engine before shutdown.
     * This is a virtual method that can be overridden by derived classes
     * to perform application-specific cleanup before the engine shuts down.
     */
    virtual void onDestroy();

protected:

    SDL_Window* m_window;
    Engine m_engine;
};

} // namespace polaris

#endif // POLARIS_APPLICATION_H 