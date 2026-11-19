#include "common.h"
#include "movie.h"

int initAll(int sector, int size, int language);
int readMpeg(VideoDec *decoder, ReadBuf *buffer, StrFile *file);
void termAll(void);

enum {
    MOVIE_THREAD_PRIORITY = 1
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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", isAudioOK);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", initAll__Fiii);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", termAll__Fv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", ErrMessage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/movie", proceedAudio__Fv);
