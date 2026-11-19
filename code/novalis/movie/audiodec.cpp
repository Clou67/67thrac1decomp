#include "audiodec.h"
#include "common.h"
#include "framebuf.h"

extern unsigned char *movieAdpcmStagingBuffer;

int snd_InitMovieSound(int block_size, int page_size, int transfer_size, int spu_address, int left_voice, int right_voice);

enum {
    ADPCM_BLOCK_SIZE = 0x400,
    ADPCM_PAGE_SIZE = 0x1000,
    ADPCM_FRAME_SIZE = 0x10,
    ADPCM_FLAGS_OFFSET = 1,
    ADPCM_LOOP_END = 1,
    ADPCM_LOOP_REPEAT = 2,
    ADPCM_LOOP_START = 4,
    STREAM_HEADER_SIZE = sizeof(SpuStreamHeader) + sizeof(SpuStreamBody)
};

int audioDecCreate(_AudioDec *decoder, unsigned char *buffer, int buffer_size, unsigned char *staging_buffer)
{
    FastMemSetZero(&decoder->sshd, sizeof(decoder->sshd));
    decoder->data = buffer;
    decoder->size = buffer_size;
    decoder->type = sceMpegStrADPCM;
    decoder->state = AUDIO_DEC_HEADER_PENDING;
    decoder->hdrCount = 0;
    decoder->put = 0;
    decoder->count = 0;
    decoder->totalBytes = 0;
    decoder->iopLastPos = 0;
    decoder->totalBytesSent = 0;
    decoder->iopZero = 0;
    decoder->spuPos = 0;
    movieAdpcmStagingBuffer = staging_buffer;
    decoder->iopBuffSize = ADPCM_BLOCK_SIZE;
    int movie_handle = snd_InitMovieSound(ADPCM_BLOCK_SIZE, ADPCM_PAGE_SIZE, ADPCM_BLOCK_SIZE, 0, 5, 3);
    decoder->iopBuff = movie_handle;

    if (movie_handle < 0)
        return 0;

    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", audioDecDelete__FP9_AudioDec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", func_0031AB58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", audioDecStart);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", audioDecReset__FP9_AudioDec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", audioDecBeginPut__FP9_AudioDecPPUcPiT1T2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", audioDecEndPut__FP9_AudioDeci);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", audioDecIsPageFull);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", audioDecSend);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", sendToSPU__FP9_AudioDecPUcii);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/audiodec", sendADPCM__FP9_AudioDec);
