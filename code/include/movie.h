#ifndef MOVIE_H
#define MOVIE_H

#include "audiodec.h"
#include "readbuf.h"
#include "sce.h"
#include "strfile.h"
#include "vobuf.h"

struct MpegDecoder;
struct sceMpegCbData;

struct sceMpeg {
    int width;
    int height;
    int frameCount;
    long long pts;
    long long dts;
    unsigned long flags;
    long long pts2nd;
    long long dts2nd;
    unsigned long flags2nd;
    MpegDecoder *sys;
};

struct TimeStamp {
    long long pts;
    long long dts;
    int pos;
    int len;
};

struct ViBuf {
    u_long128 *data;
    u_long128 *tag;
    int n;
    int dmaStart;
    int dmaN;
    int readBytes;
    int buffSize;
    unsigned int d4madr;
    unsigned int d4tadr;
    unsigned int d4qwc;
    unsigned int d4chcr;
    unsigned int d3madr;
    unsigned int d3qwc;
    unsigned int d3chcr;
    unsigned int ipubp;
    unsigned int ipuctrl;
    int sema;
    int isActive;
    long long totalBytes;
    TimeStamp *ts;
    int n_ts;
    int count_ts;
    int wt_ts;
};

struct VideoDec {
    sceMpeg mpeg;
    ViBuf vibuf;
    unsigned int state;
    int sema;
    int hid_endimage;
    int hid_vblank;
};

enum {
    MOVIE_INPUT_SECTOR_SIZE = 0x800,
    MOVIE_INPUT_SECTORS = 0x100,
    MOVIE_TIMESTAMP_COUNT = 0x200,
    MOVIE_AUDIO_BUFFER_SIZE = 0x2000,
    MOVIE_DECODER_STACK_SIZE = 0x4000
};

struct MoviePlayer {
    ReadBuf read_buf;
    unsigned char unk_5000c[0x34];
    unsigned char audio_buf[MOVIE_AUDIO_BUFFER_SIZE];
    unsigned char vi_buf_data[MOVIE_INPUT_SECTORS][MOVIE_INPUT_SECTOR_SIZE];
    unsigned char decoder_stack[MOVIE_DECODER_STACK_SIZE];
    TimeStamp vi_buf_ts[MOVIE_TIMESTAMP_COUNT];
    StrFile str_file;
    VideoDec video_dec;
    _AudioDec audio_dec;
    unsigned char unk_d9164[4];
    VoBuf vo_buf;
};

extern MoviePlayer *moviePlayer;
extern unsigned char *movieDecoderBuffer;
extern int movieDecoderThread;

int playMpegMovie(int sector, int size, unsigned char *decoder_buffer, MoviePlayer *player, int language);

#endif
