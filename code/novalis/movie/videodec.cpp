#include "common.h"
#include "movie.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecCreate__FP8VideoDecPUciPUxT3iP9TimeStampi);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", func_0031CA70);

int videoDecSetStream(VideoDec *decoder, int type, int channel, MpegStreamCallback callback, void *argument)
{
    sceMpegAddStrCallback(&decoder->mpeg, type, channel, callback, argument);
    return 1;
}

int videoDecBeginPut(VideoDec *decoder, unsigned char **first, int *firstSize, unsigned char **second, int *secondSize)
{
    return viBufBeginPut(&decoder->vibuf, first, firstSize, second, secondSize);
}

void videoDecEndPut(VideoDec *decoder, int size)
{
    viBufEndPut(&decoder->vibuf, size);
}

void videoDecReset(VideoDec *decoder)
{
    decoder->state = 0;
}

int videoDecDelete(VideoDec *decoder)
{
    viBufDelete(&decoder->vibuf);
    videoDecRelease(&decoder->mpeg);
    return 1;
}

void videoDecAbort(VideoDec *decoder)
{
    decoder->state = 1;
}

unsigned int videoDecGetState(VideoDec *decoder)
{
    return decoder->state;
}

unsigned int videoDecSetState(VideoDec *decoder, unsigned int state)
{
    unsigned int oldState = decoder->state;
    decoder->state = state;
    return oldState;
}

void videoDecPutTs(VideoDec *decoder, long pts, long dts, unsigned char *position, int size)
{
    TimeStamp timestamp;
    timestamp.pts = pts;
    timestamp.dts = dts;
    timestamp.pos = position - (unsigned char *)decoder->vibuf.data;
    timestamp.len = size;
    viBufPutTs(&moviePlayer->video_dec.vibuf, &timestamp);
}

int videoDecInputCount(VideoDec *decoder)
{
    return viBufCount(&decoder->vibuf);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", func_0031CBA8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecFlush__FP8VideoDec);

int videoDecIsFlushed(VideoDec *decoder)
{
    int flushed = 0;
    if (videoDecInputCount(decoder) == 0)
        flushed = videoDecIsDecoderEmpty(&decoder->mpeg) > 0;
    return flushed;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecMain__FPv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", decBs0__FP8VideoDec);

extern const char videoErrorMessage[];
void printf_stub(const char *format, ...);

int mpegError(sceMpeg *mpeg, sceMpegCbDataError *data, void *argument)
{
    printf_stub(videoErrorMessage, data->message);
    return 1;
}

int mpegNodata(sceMpeg *mpeg, sceMpegCbData *data, void *argument)
{
    switchThread();
    viBufAddDMA(&moviePlayer->video_dec.vibuf);
    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", func_0031CF88);

int mpegRestartVideoDMA(void)
{
    viBufRestartDMA(&moviePlayer->video_dec.vibuf);
    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", FUN_0031cfe8);
