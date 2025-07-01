#include "VideoDecoder.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace polaris {

VideoDecoder::VideoDecoder()
    : m_width(1920)
    , m_height(1080)
    , m_duration(60.0)
    , m_frameRate(30.0)
    , m_isOpen(false)
    , m_isInitialized(false)
    , m_frameCounter(0)
    , m_currentTime(0.0) {
}

VideoDecoder::~VideoDecoder() {
    close();
}

bool VideoDecoder::initialize() {
    if (m_isInitialized) {
        return true;
    }

    m_isInitialized = true;
    std::cout << "VideoDecoder initialized (demo mode)" << std::endl;
    return true;
}

bool VideoDecoder::openFile(const std::string& filename) {
    if (!m_isInitialized) {
        if (!initialize()) {
            return false;
        }
    }

    close(); // Close any previously opened file

    // For demo purposes, we'll accept any filename and create demo content
    m_isOpen = true;
    m_frameCounter = 0;
    m_currentTime = 0.0;
    
    std::cout << "Video file opened (demo): " << filename << std::endl;
    std::cout << "Resolution: " << m_width << "x" << m_height << std::endl;
    std::cout << "Duration: " << m_duration << " seconds" << std::endl;
    std::cout << "Frame rate: " << m_frameRate << " fps" << std::endl;

    return true;
}

bool VideoDecoder::getNextFrame(VideoFrame& frame) {
    if (!m_isOpen) {
        return false;
    }

    // Check if we've reached the end
    if (m_currentTime >= m_duration) {
        return false;
    }

    // Generate demo frame
    generateDemoFrame(frame);
    
    // Update timing
    m_currentTime += 1.0 / m_frameRate;
    m_frameCounter++;

    return true;
}

bool VideoDecoder::seekTo(double timeInSeconds) {
    if (timeInSeconds < 0.0 || timeInSeconds > m_duration) {
        return false;
    }

    m_currentTime = timeInSeconds;
    m_frameCounter = (int)(timeInSeconds * m_frameRate);
    
    std::cout << "Seeked to: " << timeInSeconds << " seconds" << std::endl;
    return true;
}

void VideoDecoder::close() {
    cleanup();
    m_isOpen = false;
}

void VideoDecoder::cleanup() {
    m_frameCounter = 0;
    m_currentTime = 0.0;
}

void VideoDecoder::generateDemoFrame(VideoFrame& frame) {
    frame.width = m_width;
    frame.height = m_height;
    frame.pts = m_frameCounter;
    frame.timestamp = m_currentTime;
    
    // Allocate frame data (RGB24 format)
    int dataSize = m_width * m_height * 3;
    frame.data.resize(dataSize);
    
    // Generate a random color for this frame (much faster than animated pattern)
    uint8_t r = (uint8_t)(rand() % 256);
    uint8_t g = (uint8_t)(rand() % 256);
    uint8_t b = (uint8_t)(rand() % 256);
    
    // Fill the entire frame with the same color
    for (int i = 0; i < dataSize; i += 3) {
        frame.data[i] = r;     // Red
        frame.data[i + 1] = g; // Green
        frame.data[i + 2] = b; // Blue
    }
    
    // Debug output every 30 frames (once per second at 30fps)
    if (m_frameCounter % 30 == 0) {
        std::cout << "Generated frame " << m_frameCounter 
                  << " at time " << m_currentTime 
                  << "s, data size: " << frame.data.size() 
                  << " bytes, color: R=" << (int)r << " G=" << (int)g << " B=" << (int)b << std::endl;
    }
}

} // namespace polaris 