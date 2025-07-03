#ifndef POLARIS_VIDEODECODER_H
#define POLARIS_VIDEODECODER_H

#include <string>
#include <memory>
#include <vector>

namespace polaris {

struct VideoFrame {
    std::vector<uint8_t> data;
    int width;
    int height;
    int64_t pts;  // Presentation timestamp
    double timestamp;
};

class VideoDecoder {
public:
    VideoDecoder();
    ~VideoDecoder();

    // Initialize the decoder
    virtual bool initialize();
    
    // Open and decode a video file
    virtual bool openFile(const std::string& filename);
    
    // Get next frame
    virtual bool getNextFrame(VideoFrame& frame);
    
    // Seek to specific time
    virtual bool seekTo(double timeInSeconds);
    
    // Get video information
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    double getDuration() const { return m_duration; }
    double getFrameRate() const { return m_frameRate; }
    bool isOpen() const { return m_isOpen; }
    
    // Cleanup
    virtual void close();

protected:
    // Video properties
    int m_width;
    int m_height;
    double m_duration;
    double m_frameRate;
    
    // State
    bool m_isOpen;
    bool m_isInitialized;
    
    // Frame counter for demo
    int m_frameCounter;
    double m_currentTime;
    
    // Helper methods
    virtual void cleanup();
    void generateDemoFrame(VideoFrame& frame);
};

} // namespace polaris

#endif // POLARIS_VIDEODECODER_H 