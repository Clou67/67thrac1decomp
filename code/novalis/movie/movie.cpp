#include "common.h"
#include "movie.h"
#include "pad.h"
#include "sound.h"

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

enum {
    MOVIE_SKIP_DISABLED = -1,
    MOVIE_SKIP_ANY_BUTTON = 2,
    MOVIE_DECODER_END = 3,
    MOVIE_READ_SIZE = 0x10000,
    MOVIE_MIN_DEMUX_SIZE = 5,
    MOVIE_SOUND_GROUP = 5
};

// The skip mode is sampled again when checking whether Start is allowed.
extern volatile int decodeMode;
extern int movieSkipEnabled;
extern int ChallengeMode;
extern int Level;

struct MovieAudioState {
    unsigned char unk_00[0x48];
    int group_volume[6];
};
extern MovieAudioState audioState;

void UpdatePad(void);
void switchThread(void);
int isAudioOK(void);
void proceedAudio(void);
int videoDecAbort(VideoDec *decoder);
unsigned int videoDecGetState(VideoDec *decoder);
int videoDecFlush(VideoDec *decoder);
int videoDecIsFlushed(VideoDec *decoder);
void startDisplay(int wait);
void endDisplay(void);
void snd_SetMasterVolume(int group, int volume);

static inline int movieButtonPressed(PAD *pad, int mask)
{
    return pad->bitsOn & mask;
}

static inline int movieSkipChord(PAD *pad, unsigned long mask)
{
    if ((*(unsigned long *)&pad->bits & mask) != mask)
        return 0;

    return 1;
}

int readMpeg(VideoDec *decoder, ReadBuf *buffer, StrFile *file)
{
    const unsigned long skip_chord = ((unsigned long)PAD_START << 32)
                                   | PAD_L1 | PAD_L2 | PAD_R1 | PAD_R2;
    unsigned char *write_ptr;
    unsigned char *read_ptr;
    int skipped = 0;
    int started = 0;
    int decode_remaining = file->size;
    int read_remaining = decode_remaining;

    FlushCache(0);
    FlushCache(2);
    sceGsSyncV(0);

    while (decode_remaining >= MOVIE_MIN_DEMUX_SIZE && videoDecGetState(decoder) != MOVIE_DECODER_END) {
        UpdatePad();
        int skip_mode = decodeMode;

        if (skip_mode != MOVIE_SKIP_DISABLED) {
            int skip;

            if ((skip_mode == MOVIE_SKIP_ANY_BUTTON && movieButtonPressed(&padState, -1)) ||
                ((movieSkipEnabled != 0 || ChallengeMode != 0 || decodeMode != 0 || Level <= 0) &&
                 movieButtonPressed(&padState, PAD_START)))
                skip = 1;

            else
                skip = movieSkipChord(&padState, skip_chord);

            if (skip) {
                skipped = 1;
                videoDecAbort(&moviePlayer->video_dec);
            }
        }

        int space = readBufBeginPut(buffer, &write_ptr);

        if (read_remaining > 0 && space >= MOVIE_READ_SIZE) {
            int transferred = strFileRead(file, write_ptr, MOVIE_READ_SIZE, 0);
            read_remaining -= transferred;
            readBufEndPut(buffer, transferred);
        }

        proceedAudio();
        switchThread();

        int available = readBufBeginGet(buffer, &read_ptr);

        if (available > 0) {
            int transferred = sceMpegDemuxPssRing(&decoder->mpeg, read_ptr, available, buffer, buffer->capacity);
            decode_remaining -= transferred;
            readBufEndGet(buffer, transferred);
        }

        proceedAudio();

        if (!started && voBufIsFull(&moviePlayer->vo_buf) && isAudioOK()) {
            started = 1;
            startDisplay(1);
            audioDecStart(&moviePlayer->audio_dec);
        }
    }

    while (!videoDecFlush(decoder)) {
        proceedAudio();
        switchThread();
    }

    while (!videoDecIsFlushed(decoder) && videoDecGetState(decoder) != MOVIE_DECODER_END) {
        proceedAudio();
        switchThread();
    }

    endDisplay();
    audioDecReset(&moviePlayer->audio_dec);
    snd_SetMasterVolume(MOVIE_SOUND_GROUP, audioState.group_volume[MOVIE_SOUND_GROUP]);
    snd_FlushSoundCommands();

    return skipped;
}

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

void proceedAudio(void)
{
    audioDecSend(&moviePlayer->audio_dec);
}
