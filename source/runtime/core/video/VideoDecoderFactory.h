#ifndef POLARIS_VIDEODECODERFACTORY_H
#define POLARIS_VIDEODECODERFACTORY_H

#include "VideoDecoder.h"
#include <memory>
#include <string>

namespace polaris {

enum class DecoderType {
    Demo,
    FFmpeg
};

class VideoDecoderFactory {
public:
    static std::unique_ptr<VideoDecoder> createDecoder(DecoderType type);
    static std::unique_ptr<VideoDecoder> createBestAvailableDecoder();
    
private:
    static bool isFFmpegAvailable();
};

} // namespace polaris

#endif // POLARIS_VIDEODECODERFACTORY_H 