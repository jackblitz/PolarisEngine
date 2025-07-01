#include "Application.h"
#include <iostream>
#include <stdexcept>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Logger.h"
#include "/rendering/VideoRenderer.h"
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
    extern "C"
    int main(int argc, char *argv[]) {
        (void)argc;
        (void)argv;
 std::cerr << "Library Called: " << SDL_GetError() << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create window with better error handling
    SDL_Window *window = SDL_CreateWindow(
        "Vega42 - SDL3 + Vulkan",
        1920, 1080, // 4K resolution for video
        SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Show the window after creation
    SDL_ShowWindow(window);

    // Create video renderer
    polaris::VideoRenderer videoRenderer;

    if (!videoRenderer.initialize(window)) {
        std::cerr << "Failed to initialize video renderer!" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Load the video file
    std::string videoPath = "resources/Life Untouched 4K Demo.mp4";
    if (!videoRenderer.loadVideo(videoPath)) {
        std::cerr << "Failed to load video: " << videoPath << std::endl;
        std::cerr << "Make sure the video file exists in the resources directory." << std::endl;
        std::cerr << "Running in demo mode with generated video content." << std::endl;
    }

    // Start playing the video
    videoRenderer.play();

    std::cout << "Video player started. Press:" << std::endl;
    std::cout << "  SPACE - Play/Pause" << std::endl;
    std::cout << "  ESC - Quit" << std::endl;
    std::cout << "  LEFT/RIGHT - Seek backward/forward" << std::endl;
    std::cout << "  R - Restart video" << std::endl;

    // Main loop
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;

                        case SDLK_SPACE:
                            if (videoRenderer.isPlaying()) {
                                videoRenderer.pause();
                            } else {
                                videoRenderer.play();
                            }
                            break;

                        case SDLK_LEFT:
                            videoRenderer.seek(videoRenderer.getCurrentTime() - 10.0);
                            break;

                        case SDLK_RIGHT:
                            videoRenderer.seek(videoRenderer.getCurrentTime() + 10.0);
                            break;

                        case SDLK_R:
                            videoRenderer.stop();
                            videoRenderer.play();
                            break;
                    }
                    break;
            }
        }
        std::cout << "Update:" << std::endl;
        // Update video
        videoRenderer.update();

        // Render video
        videoRenderer.render();

        // Cap frame rate
        SDL_Delay(0); // ~60 FPS
    }

    // Cleanup
    videoRenderer.shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Video player closed." << std::endl;
        return 0;
    }
} // namespace polaris