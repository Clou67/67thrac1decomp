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

void *LibcMemcpy(void *destination, const void *source, unsigned int size);

int cpy2area(unsigned char *first, int firstSize, unsigned char *second, int secondSize,
             unsigned char *source, int sourceSize, unsigned char *wrapped, int wrappedSize)
{
    if (firstSize + secondSize < sourceSize + wrappedSize)
        return 0;
    if (sourceSize >= firstSize) {
        LibcMemcpy(first, source, firstSize);
        LibcMemcpy(second, source + firstSize, sourceSize - firstSize);
        LibcMemcpy(second + sourceSize - firstSize, wrapped, wrappedSize);
    } else {
        int remaining = firstSize - sourceSize;
        if (wrappedSize >= remaining) {
            LibcMemcpy(first, source, sourceSize);
            LibcMemcpy(first + sourceSize, wrapped, remaining);
            LibcMemcpy(second, wrapped + firstSize - sourceSize, wrappedSize - remaining);
        } else {
            LibcMemcpy(first, source, sourceSize);
            LibcMemcpy(first + sourceSize, wrapped, wrappedSize);
        }
    }
    return sourceSize + wrappedSize;
}
