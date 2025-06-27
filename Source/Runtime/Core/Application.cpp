#include "Application.h"
#include <iostream>
#include <stdexcept>
#include "Logger.h"

namespace polaris {

Application::Application() : m_window(nullptr) {
    LOG_INFO("Application constructed");
}

Application::~Application() {
    LOG_INFO("Application destructed");
}

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

void Application::run() {
    LOG_INFO("Application Running...");
    m_engine.run();
}

void Application::setWindow(SDL_Window* window) {
    if (!window) {
        LOG_ERROR("Cannot set null window");
        throw std::invalid_argument("Cannot set null window");
    }
    
    m_window = window;
    OnCreated();
}

void Application::OnCreated() {
    LOG_INFO("Application OnCreated: Window is now available.");
}

void Application::onDestroy() {
    LOG_INFO("Application onDestroy: Cleaning up application resources.");
}

} // namespace polaris 