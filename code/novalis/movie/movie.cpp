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

struct MovieDecoderMemory {
    VoData output_frames[2];
    VoTag output_tags[2];
    u_long128 input_tags[MOVIE_INPUT_SECTORS + 1];
    unsigned char adpcm_staging[0x400];
    unsigned char unk_1c8590[0x30];
    unsigned char mpeg_work[0xEB768];
};

struct sceMpegCbDataStr;
typedef int (*MpegStreamCallback)(sceMpeg *, sceMpegCbData *, void *);

int videoDecCreate(VideoDec *decoder, unsigned char *work, int work_size, unsigned long long *input,
                   unsigned long long *tags, int sectors, TimeStamp *timestamps, int timestamp_count);
int videoDecSetStream(VideoDec *decoder, int type, int channel, MpegStreamCallback callback, void *argument);
int videoCallback(sceMpeg *mpeg, sceMpegCbData *event, void *argument);
int pcmCallback(sceMpeg *mpeg, sceMpegCbDataStr *event, void *argument);
void videoDecMain(void *argument);
int vblankHandler(int cause);
int handler_endimage(int channel);
extern int _gp;
extern const char movieOpenError[];

int initAll(int sector, int size, int language)
{
    const unsigned int dma_enable = 1;
    const unsigned int gif_acknowledge = 1 << MOVIE_GIF_DMA_CHANNEL;
    volatile unsigned int *const dma_control = (volatile unsigned int *)DMA_CONTROL_ADDRESS;
    volatile unsigned int *const dma_status = (volatile unsigned int *)0x1000E010;
    EeThreadParams thread;
    int opened;

    *dma_control |= dma_enable | DMA_CONTROL_RELEASE;
    *dma_status = gif_acknowledge;
    readBufCreate(&moviePlayer->read_buf);
    sceMpegInit();

    videoDecCreate(&moviePlayer->video_dec, ((MovieDecoderMemory *)movieDecoderBuffer)->mpeg_work,
                   sizeof(((MovieDecoderMemory *)movieDecoderBuffer)->mpeg_work),
                   (unsigned long long *)moviePlayer->vi_buf_data,
                   (unsigned long long *)((MovieDecoderMemory *)movieDecoderBuffer)->input_tags, MOVIE_INPUT_SECTORS,
                   moviePlayer->vi_buf_ts, MOVIE_TIMESTAMP_COUNT);
    audioDecCreate(&moviePlayer->audio_dec, moviePlayer->audio_buf, MOVIE_AUDIO_BUFFER_SIZE,
                   ((MovieDecoderMemory *)movieDecoderBuffer)->adpcm_staging);
    videoDecSetStream(&moviePlayer->video_dec, sceMpegStrM2V, 0, videoCallback, &moviePlayer->read_buf);
    videoDecSetStream(&moviePlayer->video_dec, sceMpegStrADPCM, language,
                      (MpegStreamCallback)pcmCallback, &moviePlayer->read_buf);

    voBufCreate(&moviePlayer->vo_buf,
                (VoData *)(((unsigned int)((MovieDecoderMemory *)movieDecoderBuffer)->output_frames & 0x0FFFFFFF) | 0x20000000),
                ((MovieDecoderMemory *)movieDecoderBuffer)->output_tags, sizeof(((MovieDecoderMemory *)movieDecoderBuffer)->output_frames) / sizeof(VoData));

    thread.stack = moviePlayer->decoder_stack;
    thread.entry = videoDecMain;
    thread.stack_size = MOVIE_DECODER_STACK_SIZE;
    thread.priority = MOVIE_THREAD_PRIORITY;
    thread.gp = &_gp;
    thread.option = 0;
    int thread_id = CreateThread(&thread);
    movieDecoderThread = thread_id;
    _StartThread(thread_id, &moviePlayer->video_dec);

    if (!strFileBegin(&moviePlayer->str_file, sector, size)) {
        opened = 0;
        printf_stub(movieOpenError);
    }

    else {
        opened = 1;
    }

    moviePlayer->video_dec.hid_vblank = AddIntcHandler(MOVIE_VBLANK_INTERRUPT, vblankHandler, 0);
    EnableIntc(MOVIE_VBLANK_INTERRUPT);
    moviePlayer->video_dec.hid_endimage = AddDmacHandler(MOVIE_GIF_DMA_CHANNEL, handler_endimage, 0);
    EnableDmac(MOVIE_GIF_DMA_CHANNEL);

    return opened;
}

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
