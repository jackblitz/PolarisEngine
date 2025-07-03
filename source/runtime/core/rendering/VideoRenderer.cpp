#include "VideoRenderer.h"
#include <iostream>
#include <stdexcept>
#include <VideoDecoder.h>

namespace polaris {

VideoRenderer::VideoRenderer() 
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_videoTexture(nullptr)
    , m_decoder(VideoDecoderFactory::createBestAvailableDecoder())
    , m_isPlaying(false)
    , m_isLoaded(false)
    , m_duration(0.0)
    , m_currentTime(0.0)
    , m_frameRate(30.0)
    , m_videoWidth(0)
    , m_videoHeight(0)
    , m_lastFrameTime(0)
    , m_frameDelay(0) {
}

VideoRenderer::~VideoRenderer() {
    shutdown();
}

bool VideoRenderer::initialize(SDL_Window* window) {
    if (!window) {
        std::cerr << "VideoRenderer: Invalid window pointer" << std::endl;
        return false;
    }
    
    m_window = window;
    
    // Create renderer for video
    m_renderer = SDL_CreateRenderer(window, nullptr);
    if (!m_renderer) {
        std::cerr << "VideoRenderer: Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Set renderer properties for video
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    
    // Initialize video decoder
    if (!m_decoder->initialize()) {
        std::cerr << "VideoRenderer: Failed to initialize video decoder" << std::endl;
        return false;
    }
    
    std::cout << "VideoRenderer initialized successfully" << std::endl;
    return true;
}

bool VideoRenderer::loadVideo(const std::string& videoPath) {
    if (!m_renderer) {
        std::cerr << "VideoRenderer: Renderer not initialized" << std::endl;
        return false;
    }
    
    m_videoPath = "/Life Untouched 4k Demo.mp4";
    
    // Try to open video file with decoder
    if (!m_decoder->openFile(videoPath)) {
        std::cerr << "VideoRenderer: Failed to open video file: " << videoPath << std::endl;
        std::cerr << "VideoRenderer: Falling back to demo mode" << std::endl;
        
        // Fall back to demo mode - create a demo video
        m_videoWidth = 1920;
        m_videoHeight = 1080;
        m_duration = 60.0;
        m_frameRate = 30.0;
        
        // Create texture for demo frames
        if (!createTexture()) {
            std::cerr << "VideoRenderer: Failed to create demo texture" << std::endl;
            return false;
        }
        
        m_currentTime = 0.0;
        m_isLoaded = true;
        calculateFrameDelay();
        
        std::cout << "Demo video loaded with resolution: " << m_videoWidth << "x" << m_videoHeight << std::endl;
        return true;
    }
    
    // Get video properties from decoder
    m_videoWidth = m_decoder->getWidth();
    m_videoHeight = m_decoder->getHeight();
    m_duration = m_decoder->getDuration();
    m_frameRate = m_decoder->getFrameRate();
    
    // Create texture for video frames
    if (!createTexture()) {
        std::cerr << "VideoRenderer: Failed to create video texture" << std::endl;
        return false;
    }
    
    m_currentTime = 0.0;
    m_isLoaded = true;
    
    calculateFrameDelay();
    
    std::cout << "Video loaded: " << videoPath << std::endl;
    std::cout << "Resolution: " << m_videoWidth << "x" << m_videoHeight << std::endl;
    std::cout << "Duration: " << m_duration << " seconds" << std::endl;
    std::cout << "Frame rate: " << m_frameRate << " fps" << std::endl;
    
    return true;
}

void VideoRenderer::update() {
    if (!m_isLoaded || !m_isPlaying) {
        return;
    }
    
    Uint32 currentTime = SDL_GetTicks();
    
    // Check if it's time for the next frame
   // if (currentTime - m_lastFrameTime >= m_frameDelay) {
        // Load next frame from decoder
        if (loadNextFrame()) {
            m_currentTime = m_currentFrame.timestamp;
            m_lastFrameTime = currentTime;
            
            // Only update texture if we have valid frame data
            if (!m_currentFrame.data.empty()) {
                updateTexture();
            }
        } else {
            // End of video reached, loop back to start
            m_decoder->seekTo(0.0);
            m_currentTime = 0.0;
        }
   // }
}

void VideoRenderer::render() {
    if (!m_renderer || !m_videoTexture) {
        return; // Silent return to reduce error spam
    }
    
    // Get texture properties for debugging
    static int debugCount = 0;
    debugCount++;
    if (debugCount % 120 == 0) { // Reduced frequency
        std::cout << "Expected texture size: " << m_videoWidth << "x" << m_videoHeight << std::endl;
    }
    
    // Clear renderer
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    
    // Get window size for scaling
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);
    
    // Try a very simple rendering approach - just render the texture at its original size
    SDL_FRect destRect = {0.0f, 0.0f, (float)m_videoWidth, (float)m_videoHeight};
    
    // Debug output every 60 frames (reduced frequency)
    static int renderCount = 0;
    renderCount++;
    if (renderCount % 60 == 0) {
        std::cout << "Rendering frame " << renderCount 
                  << ", window: " << windowWidth << "x" << windowHeight
                  << ", dest: " << destRect.x << "," << destRect.y 
                  << " " << destRect.w << "x" << destRect.h << std::endl;
    }
    
    // Try rendering with original texture size
    int renderResult = SDL_RenderTexture(m_renderer, m_videoTexture, nullptr, &destRect);
    if (renderResult != 0) {
        // Only show error every 60 frames to reduce spam
        static int renderErrorCount = 0;
        renderErrorCount++;
        if (renderErrorCount % 60 == 0) {
            std::cerr << "Failed to render texture (frame " << renderErrorCount << "): " << SDL_GetError() << std::endl;
        }
    }
    
    // Present renderer
    SDL_RenderPresent(m_renderer);
}

void VideoRenderer::play() {
    if (m_isLoaded) {
        m_isPlaying = true;
        m_lastFrameTime = SDL_GetTicks();
        std::cout << "Video playback started" << std::endl;
    }
}

void VideoRenderer::pause() {
    m_isPlaying = false;
    std::cout << "Video playback paused" << std::endl;
}

void VideoRenderer::stop() {
    m_isPlaying = false;
    m_currentTime = 0.0;
    m_decoder->seekTo(0.0);
    std::cout << "Video playback stopped" << std::endl;
}

void VideoRenderer::seek(double timeInSeconds) {
    if (timeInSeconds >= 0.0 && timeInSeconds <= m_duration) {
        if (m_decoder->seekTo(timeInSeconds)) {
            m_currentTime = timeInSeconds;
            // Load the frame at the new position
            if (loadNextFrame()) {
                updateTexture();
            }
            std::cout << "Video seeked to: " << timeInSeconds << " seconds" << std::endl;
        }
    }
}

void VideoRenderer::shutdown() {
    if (m_videoTexture) {
        SDL_DestroyTexture(m_videoTexture);
        m_videoTexture = nullptr;
    }
    
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    
    if (m_decoder) {
        m_decoder->close();
    }
    
    m_isLoaded = false;
    m_isPlaying = false;
    
    std::cout << "VideoRenderer shutdown complete" << std::endl;
}

void VideoRenderer::calculateFrameDelay() {
    m_frameDelay = (Uint32)(1000.0 / m_frameRate); // Convert to milliseconds
}

bool VideoRenderer::createTexture() {
    // Create texture with streaming access mode (better for frequent updates)
    m_videoTexture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        m_videoWidth,
        m_videoHeight
    );
    
    if (m_videoTexture) {
        std::cout << "Created texture with size: " 
                  << m_videoWidth << "x" << m_videoHeight << std::endl;
        return true;
    } else {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return false;
    }
}

void VideoRenderer::updateTexture() {
    if (!m_videoTexture || m_currentFrame.data.empty()) {
        return; // Silent return to reduce error spam
    }
    
    // Use SDL_UpdateTexture directly (this was working before)
    int updateResult = SDL_UpdateTexture(m_videoTexture, nullptr, m_currentFrame.data.data(), m_videoWidth * 3);
    
   // if (updateResult) {
        // Debug output every 60 frames
        static int updateCount = 0;
        updateCount++;
        //if (updateCount % 60 == 0) {
            std::cout << "Updated texture " << updateCount 
                      << " times, frame size: " << m_currentFrame.data.size() 
                      << " bytes" << std::endl;
            
            // Check a few sample pixels to verify data
            if (!m_currentFrame.data.empty()) {
                std::cout << "Sample pixels - Top-left: R=" << (int)m_currentFrame.data[0] 
                          << " G=" << (int)m_currentFrame.data[1] 
                          << " B=" << (int)m_currentFrame.data[2] << std::endl;
            }
       // }
   /* } else {
        // Only show error every 60 frames to reduce spam
        static int errorCount = 0;
        errorCount++;
        if (errorCount % 60 == 0) {
            std::cerr << "Failed to update texture (frame " << errorCount << "): " << SDL_GetError() << std::endl;
        }*/
    //}
}

bool VideoRenderer::loadNextFrame() {
    if (!m_decoder || !m_decoder->isOpen()) {
        return false;
    }
    
    bool success = m_decoder->getNextFrame(m_currentFrame);
    
    // Debug output every 30 frames
    static int frameCount = 0;
    frameCount++;
    if (frameCount % 30 == 0) {
        std::cout << "Loaded frame " << frameCount 
                  << ", size: " << m_currentFrame.data.size() 
                  << " bytes, timestamp: " << m_currentFrame.timestamp 
                  << "s" << std::endl;
    }
    
    return success;
}

} // namespace polaris 