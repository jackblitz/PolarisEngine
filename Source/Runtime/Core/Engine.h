#ifndef POLARIS_ENGINE_H
#define POLARIS_ENGINE_H

#include <SDL3/SDL.h>

namespace polaris {
    class Application; // Forward declaration
}

namespace polaris {

class Engine {
public:
    Engine();
    ~Engine();

    void initialize();
    void run();
    void shutdown();
    
    // Set the application instance (accepts base Application pointer)
    void setApplication(polaris::Application* app);
    
    // Get the window (useful for Application)
    SDL_Window* getWindow() const { return m_window; }

private:
    SDL_Window* m_window;
    polaris::Application* m_application;
};

} // namespace polaris

#endif // POLARIS_ENGINE_H 