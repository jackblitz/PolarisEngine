#ifndef POLARIS_APPLICATION_H
#define POLARIS_APPLICATION_H

#include "Engine.h"
#include <SDL3/SDL.h>

namespace polaris {

class Application {
public:
    Application();
    virtual ~Application();

    virtual void initialize();
    virtual void shutdown();

    // Called by Engine when the window is created
    void setWindow(SDL_Window* window);
    void bindApplication(); // Called on devices like android when the surface needs binding to the activity
    void setFullscreen(bool fullscreen);

protected:
    // Called when the window is set/created
    virtual void OnCreated();
    SDL_Window* m_window;
    Engine* m_engine;
    bool m_running = true;
};

} // namespace polaris

#endif // POLARIS_APPLICATION_H 