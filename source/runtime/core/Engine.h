#ifndef POLARIS_ENGINE_H
#define POLARIS_ENGINE_H

#include <SDL3/SDL.h>
#include "rendering/PlatformRenderer.h"

namespace polaris {
    class Application; // Forward declaration
}

namespace polaris {

class Engine {
public:
    /**
     * @brief Constructs an Engine object.
     * Initializes internal pointers to null.
     */
    Engine();

    /**
     * @brief Destroys the Engine object.
     * Cleans up SDL resources, including destroying the window and quitting SDL subsystems.
     */
    ~Engine();

    /**
     * @brief Initializes the engine.
     * This method initializes SDL, creates the application window, and sets up the application instance.
     * It also handles error logging if SDL or window creation fails.
     */
    void initialize();

    /**
     * @brief Runs the main engine loop.
     * This method handles SDL events and keeps the engine running until a quit event is received.
     */
    void run();
    
    /**
     * @brief Sets the application instance for the engine.
     * This allows the engine to communicate with the application, particularly for window events.
     * @param app A pointer to the Application instance.
     */
    void setApplication(polaris::Application* app);

    /**
     * @brief Shuts down the engine.
     * This method cleans up any remaining resources and prepares the engine for termination.
     */
    void shutdown();


private:
    /**
     * @brief Pointer to the SDL window.
     */
    SDL_Window* m_window;
    /**
     * @brief Pointer to the platform-specific renderer.
     */
    PlatformRenderer* m_renderer;
    /**
     * @brief Pointer to the application instance.
     */
    polaris::Application* m_application;

};

} // namespace polaris

#endif // POLARIS_ENGINE_H 