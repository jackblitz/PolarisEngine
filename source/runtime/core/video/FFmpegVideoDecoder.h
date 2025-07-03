#ifndef POLARIS_FFMPEGVIDEODECODER_H
#define POLARIS_FFMPEGVIDEODECODER_H

#include "VideoDecoder.h"
#include <string>
#include <memory>

// FFmpeg includes - commented out for now to avoid compilation issues
/*
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
}
*/

namespace polaris {

class FFmpegVideoDecoder : public VideoDecoder {
public:
    FFmpegVideoDecoder();
    ~FFmpegVideoDecoder();

    // Override base class methods
    bool initialize() override;
    bool openFile(const std::string& filename) override;
    bool getNextFrame(VideoFrame& frame) override;
    bool seekTo(double timeInSeconds) override;
    void close() override;

    // Additional FFmpeg-specific methods
    bool isFFmpegAvailable() const { return m_ffmpegInitialized; }
    
private:
    // FFmpeg context - using void pointers for now
    void* m_formatContext;
    void* m_codecContext;
    void* m_videoStream;
    void* m_frame;
    void* m_rgbFrame;
    void* m_packet;
    void* m_swsContext;
    
    // FFmpeg state
    bool m_ffmpegInitialized;
    int m_videoStreamIndex;
    
    // Frame conversion
    uint8_t* m_rgbBuffer;
    int m_rgbBufferSize;
    
    // Helper methods
    void cleanup();
    bool initializeFFmpeg();
    bool openVideoFile(const std::string& filename);
    bool setupVideoStream();
    bool setupFrameConversion();
    bool decodeNextFrame(VideoFrame& frame);
    void convertFrameToRGB(VideoFrame& frame);
    double getFrameTimestamp(void* frame, void* timeBase);
};

} // namespace polaris

#endif // POLARIS_FFMPEGVIDEODECODER_H 