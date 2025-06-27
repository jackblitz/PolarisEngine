#include "Application.h"
#include "Engine.h"
#include <iostream>

namespace polaris {

Application::Application() : m_window(nullptr) {
    std::cout << "Application constructed." << std::endl;
}

Application::~Application() {
    std::cout << "Application destructed." << std::endl;
}

void Application::initialize() {
    std::cout << "Application initialized." << std::endl;
    m_engine.setApplication(this);  // Pass 'this' to the Engine
    m_engine.initialize();
}

void Application::run() {
    m_engine.run();
}

void Application::setWindow(SDL_Window* window) {
    m_window = window;
    OnCreated();
}

void Application::OnCreated() {
    std::cout << "Application OnCreated: Window is now available." << std::endl;
    // Show the window after engine initialization is complete
    SDL_ShowWindow(m_window);
}

} // namespace polaris 