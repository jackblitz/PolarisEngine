#include "FFmpegVideoDecoder.h"
#include <iostream>
#include <cstdlib>

namespace polaris {

FFmpegVideoDecoder::FFmpegVideoDecoder()
    : m_formatContext(nullptr)
    , m_codecContext(nullptr)
    , m_videoStream(nullptr)
    , m_frame(nullptr)
    , m_rgbFrame(nullptr)
    , m_packet(nullptr)
    , m_swsContext(nullptr)
    , m_ffmpegInitialized(false)
    , m_videoStreamIndex(-1)
    , m_rgbBuffer(nullptr)
    , m_rgbBufferSize(0) {
}

FFmpegVideoDecoder::~FFmpegVideoDecoder() {
    close();
}

bool FFmpegVideoDecoder::initialize() {
    if (m_isInitialized) {
        return true;
    }

    // For now, FFmpeg is not properly integrated, so we'll use demo mode
    std::cout << "FFmpegVideoDecoder: FFmpeg not available, using demo mode" << std::endl;
    
    // Initialize as demo decoder
    m_isInitialized = true;
    m_width = 1920;
    m_height = 1080;
    m_duration = 60.0;
    m_frameRate = 30.0;
    
    std::cout << "FFmpegVideoDecoder initialized in demo mode" << std::endl;
    return true;
}

bool FFmpegVideoDecoder::openFile(const std::string& filename) {
    if (!m_isInitialized) {
        if (!initialize()) {
            return false;
        }
    }

    close(); // Close any previously opened file

    // For now, use demo mode since FFmpeg is not properly integrated
    m_isOpen = true;
    m_frameCounter = 0;
    m_currentTime = 0.0;

    std::cout << "FFmpegVideoDecoder: Using demo mode for file: " << filename << std::endl;
    std::cout << "Resolution: " << m_width << "x" << m_height << std::endl;
    std::cout << "Duration: " << m_duration << " seconds" << std::endl;
    std::cout << "Frame rate: " << m_frameRate << " fps" << std::endl;

    return true;
}

bool FFmpegVideoDecoder::getNextFrame(VideoFrame& frame) {
    if (!m_isOpen) {
        return false;
    }

    // Check if we've reached the end
    if (m_currentTime >= m_duration) {
        return false;
    }

    // Generate demo frame (same as base class)
    frame.width = m_width;
    frame.height = m_height;
    frame.pts = m_frameCounter;
    frame.timestamp = m_currentTime;
    
    // Allocate frame data (RGB24 format)
    int dataSize = m_width * m_height * 3;
    frame.data.resize(dataSize);
    
    // Generate a random color for this frame
    uint8_t r = (uint8_t)(rand() % 256);
    uint8_t g = (uint8_t)(rand() % 256);
    uint8_t b = (uint8_t)(rand() % 256);
    
    // Fill the entire frame with the same color
    for (int i = 0; i < dataSize; i += 3) {
        frame.data[i] = r;     // Red
        frame.data[i + 1] = g; // Green
        frame.data[i + 2] = b; // Blue
    }
    
    // Update timing
    m_currentTime += 1.0 / m_frameRate;
    m_frameCounter++;

    return true;
}

bool FFmpegVideoDecoder::seekTo(double timeInSeconds) {
    if (timeInSeconds < 0.0 || timeInSeconds > m_duration) {
        return false;
    }

    m_currentTime = timeInSeconds;
    m_frameCounter = (int)(timeInSeconds * m_frameRate);
    
    std::cout << "FFmpegVideoDecoder: Seeked to: " << timeInSeconds << " seconds" << std::endl;
    return true;
}

void FFmpegVideoDecoder::close() {
    cleanup();
    m_isOpen = false;
}

void FFmpegVideoDecoder::cleanup() {
    // For now, just reset demo state
    m_frameCounter = 0;
    m_currentTime = 0.0;
}

// Stub implementations for FFmpeg-specific methods
bool FFmpegVideoDecoder::initializeFFmpeg() {
    return false; // Not implemented yet
}

bool FFmpegVideoDecoder::openVideoFile(const std::string& filename) {
    return false; // Not implemented yet
}

bool FFmpegVideoDecoder::setupVideoStream() {
    return false; // Not implemented yet
}

bool FFmpegVideoDecoder::setupFrameConversion() {
    return false; // Not implemented yet
}

bool FFmpegVideoDecoder::decodeNextFrame(VideoFrame& frame) {
    return false; // Not implemented yet
}

void FFmpegVideoDecoder::convertFrameToRGB(VideoFrame& frame) {
    // Not implemented yet
}

double FFmpegVideoDecoder::getFrameTimestamp(void* frame, void* timeBase) {
    return 0.0; // Not implemented yet
}

} // namespace polaris 