#ifndef POLARIS_VIDEORENDERER_H
#define POLARIS_VIDEORENDERER_H

#include <SDL3/SDL.h>
#include <string>
#include <memory>
#include "../video/VideoDecoder.h"

namespace polaris {

class VideoRenderer {
public:
    VideoRenderer();
    ~VideoRenderer();

    // Initialize video renderer
    bool initialize(SDL_Window* window);
    
    // Load and start playing a video file
    bool loadVideo(const std::string& videoPath);
    
    // Update video frame
    void update();
    
    // Render current frame
    void render();
    
    // Control playback
    void play();
    void pause();
    void stop();
    void seek(double timeInSeconds);
    bool loadNextFrame();
    // Get video info
    bool isPlaying() const { return m_isPlaying; }
    double getDuration() const { return m_duration; }
    double getCurrentTime() const { return m_currentTime; }
    int getWidth() const { return m_videoWidth; }
    int getHeight() const { return m_videoHeight; }
    
    // Cleanup
    void shutdown();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_videoTexture;
    std::unique_ptr<VideoDecoder> m_decoder;
    // Video state
    bool m_isPlaying;
    bool m_isLoaded;
    double m_duration;
    double m_currentTime;
    double m_frameRate;
    
    // Video dimensions
    int m_videoWidth;
    int m_videoHeight;
    
    // Frame timing
    Uint32 m_lastFrameTime;
    Uint32 m_frameDelay;
    
    // Video file path
    std::string m_videoPath;
    
    // Current frame data
    VideoFrame m_currentFrame;
    
    // Helper methods
    bool createTexture();
    void updateTexture();
    void calculateFrameDelay();
};

} // namespace polaris

#endif // POLARIS_VIDEORENDERER_H 