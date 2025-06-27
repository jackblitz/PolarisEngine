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
    void run();

    // Called by Engine when the window is created
    void setWindow(SDL_Window* window);

protected:
    // Called when the window is set/created
    virtual void OnCreated();
    SDL_Window* m_window;
    Engine m_engine;
};

} // namespace polaris

#endif // POLARIS_APPLICATION_H 