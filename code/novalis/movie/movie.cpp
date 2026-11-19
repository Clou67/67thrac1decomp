#include "common.h"
#include "movie.h"

int initAll(int sector, int size, int language);
int readMpeg(VideoDec *decoder, ReadBuf *buffer, StrFile *file);
void termAll(void);
void printf_stub(const char *format, ...);
int videoDecDelete(VideoDec *decoder);

enum {
    MOVIE_THREAD_PRIORITY = 1,
    MOVIE_VBLANK_INTERRUPT = 2,
    MOVIE_GIF_DMA_CHANNEL = 2,
    DMA_CONTROL_ADDRESS = 0x1000E000,
    DMA_CONTROL_RELEASE = 2
};

int playMpegMovie(int sector, int size, unsigned char *decoder_buffer, MoviePlayer *player, int language)
{
    movieDecoderBuffer = decoder_buffer;
    moviePlayer = player;
    ChangeThreadPriority(GetThreadId(), MOVIE_THREAD_PRIORITY);

    if (initAll(sector, size, language))
        readMpeg(&moviePlayer->video_dec, &moviePlayer->read_buf, &moviePlayer->str_file);

    termAll();
    movieDecoderBuffer = 0;
    moviePlayer = 0;

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", readMpeg__FP8VideoDecP7ReadBufP7StrFile);

void switchThread(void)
{
    RotateThreadReadyQueue(MOVIE_THREAD_PRIORITY);
}

int isAudioOK(void)
{
    return audioDecIsPageFull(&moviePlayer->audio_dec);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", initAll__Fiii);

void termAll(void)
{
    sceCdSync(0);
    readBufDelete(&moviePlayer->read_buf);
    voBufDelete(&moviePlayer->vo_buf);
    TerminateThread(movieDecoderThread);
    DeleteThread(movieDecoderThread);
    DisableDmac(MOVIE_GIF_DMA_CHANNEL);
    RemoveDmacHandler(MOVIE_GIF_DMA_CHANNEL, moviePlayer->video_dec.hid_endimage);
    DisableIntc(MOVIE_VBLANK_INTERRUPT);
    RemoveIntcHandler(MOVIE_VBLANK_INTERRUPT, moviePlayer->video_dec.hid_vblank);
    videoDecDelete(&moviePlayer->video_dec);
    audioDecDelete(&moviePlayer->audio_dec);
    strFileDelete(&moviePlayer->str_file);
    sceCdSync(0);
    *(unsigned int *)DMA_CONTROL_ADDRESS &= ~DMA_CONTROL_RELEASE;
}

void ErrMessage(char *message)
{
    printf_stub("[ Error ] %s\n", message);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", proceedAudio__Fv);
