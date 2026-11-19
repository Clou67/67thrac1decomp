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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecPutTs__FP8VideoDecllPUci);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecInputCount__FP8VideoDec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", func_0031CBA8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecFlush__FP8VideoDec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecIsFlushed__FP8VideoDec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecMain__FPv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", decBs0__FP8VideoDec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", mpegError__FP7sceMpegP18sceMpegCbDataErrorPv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", mpegNodata__FP7sceMpegP13sceMpegCbDataPv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", func_0031CF88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", mpegRestartVideoDMA__Fv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", FUN_0031cfe8);
