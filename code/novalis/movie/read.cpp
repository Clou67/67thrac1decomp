#include "common.h"
#include "movie.h"
#include "read.h"

struct MoviePutSpans {
    unsigned char *first;
    int firstSize;
    unsigned char *second;
    int secondSize;
};

extern char ptsOverflowMessage[];
void ErrMessage(char *message);

int videoCallback(sceMpeg *mpeg, sceMpegCbData *data, void *argument)
{
    sceMpegCbDataStr *stream = (sceMpegCbDataStr *)data;
    ReadBuf *buffer = (ReadBuf *)argument;
    MoviePutSpans spans;
    unsigned char *source = stream->data;
    int total = stream->length;
    int firstSize = buffer->data + buffer->capacity - source;
    if (total < firstSize)
        firstSize = total;
    int remaining = total - firstSize;
    videoDecBeginPut(&moviePlayer->video_dec, &spans.first, &spans.firstSize, &spans.second, &spans.secondSize);
    int copied = cpy2area((unsigned char *)(((unsigned int)spans.first & 0xFFFFFFF) | 0x20000000), spans.firstSize,
                         (unsigned char *)(((unsigned int)spans.second & 0xFFFFFFF) | 0x20000000), spans.secondSize,
                         source, firstSize, buffer->data, remaining);
    if (copied > 0) {
        if (!videoDecPutTs(&moviePlayer->video_dec, stream->pts, stream->dts, spans.first, copied))
            ErrMessage(ptsOverflowMessage);
    }
    videoDecEndPut(&moviePlayer->video_dec, copied);
    return copied > 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/read", pcmCallback__FP7sceMpegP16sceMpegCbDataStrPv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/read", cpy2area__FPUciT0iT0iT0i);
