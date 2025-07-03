#include "VideoDecoderFactory.h"
#include "FFmpegVideoDecoder.h"
#include <iostream>

namespace polaris {

std::unique_ptr<VideoDecoder> VideoDecoderFactory::createDecoder(DecoderType type) {
    switch (type) {
        case DecoderType::Demo:
            return std::make_unique<VideoDecoder>();
            
        case DecoderType::FFmpeg:
            if (isFFmpegAvailable()) {
                return std::make_unique<FFmpegVideoDecoder>();
            } else {
                std::cerr << "FFmpeg decoder not available, falling back to demo decoder" << std::endl;
                return std::make_unique<VideoDecoder>();
            }
            
        default:
            std::cerr << "Unknown decoder type, using demo decoder" << std::endl;
            return std::make_unique<VideoDecoder>();
    }
}

std::unique_ptr<VideoDecoder> VideoDecoderFactory::createBestAvailableDecoder() {
    // Try FFmpeg first, fall back to demo if not available
    if (isFFmpegAvailable()) {
        std::cout << "Using FFmpeg video decoder" << std::endl;
        return std::make_unique<FFmpegVideoDecoder>();
    } else {
        std::cout << "FFmpeg not available, using demo video decoder" << std::endl;
        return std::make_unique<VideoDecoder>();
    }
}

bool VideoDecoderFactory::isFFmpegAvailable() {
    // For now, we'll assume FFmpeg is available if we can compile with it
    // In a real implementation, you might want to check for actual library availability
    #ifdef POLARIS_FFMPEG_AVAILABLE
        return true;
    #else
        return false;
    #endif
}

} // namespace polaris 