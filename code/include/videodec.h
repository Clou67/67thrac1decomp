#ifndef VIDEODEC_H
#define VIDEODEC_H

#include "readbuf.h"
#include "sce.h"

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

struct sceMpegCbDataStr;

typedef int (*MpegStreamCallback)(sceMpeg *, sceMpegCbData *, void *);

int videoDecCreate(VideoDec *decoder, unsigned char *work, int work_size, unsigned long long *input,
                   unsigned long long *tags, int sectors, TimeStamp *timestamps, int timestamp_count);
int videoDecSetStream(VideoDec *decoder, int type, int channel, MpegStreamCallback callback, void *argument);
void videoDecAbort(VideoDec *decoder);
unsigned int videoDecGetState(VideoDec *decoder);
int videoDecFlush(VideoDec *decoder);
int videoDecIsFlushed(VideoDec *decoder);
int videoDecDelete(VideoDec *decoder);
// Entry point of the decoder thread.
void videoDecMain(void *argument);

int videoDecBeginPut(VideoDec *decoder, unsigned char **first, int *firstSize, unsigned char **second, int *secondSize);

int viBufBeginPut(ViBuf *buffer, unsigned char **first, int *firstSize, unsigned char **second, int *secondSize);

void videoDecEndPut(VideoDec *decoder, int size);

void viBufEndPut(ViBuf *buffer, int size);

void videoDecReset(VideoDec *decoder);

int viBufDelete(ViBuf *buffer);

unsigned int videoDecSetState(VideoDec *decoder, unsigned int state);

int videoDecPutTs(VideoDec *decoder, long pts, long dts, unsigned char *position, int size);

int viBufPutTs(ViBuf *buffer, TimeStamp *timestamp);

int videoDecInputCount(VideoDec *decoder);

int viBufCount(ViBuf *buffer);

int mpegNodata(sceMpeg *mpeg, sceMpegCbData *data, void *argument);

int viBufAddDMA(ViBuf *buffer);

int mpegRestartVideoDMA(void);

int viBufRestartDMA(ViBuf *buffer);

int mpegError(sceMpeg *mpeg, sceMpegCbDataError *data, void *argument);

int mpegStopVideoDMA(void);

int viBufStopDMA(ViBuf *buffer);

int mpegTimeStamp(sceMpeg *mpeg, sceMpegCbDataTimeStamp *data, void *argument);

int viBufGetTs(ViBuf *buffer, TimeStamp *timestamp);

int viBufCreate(ViBuf *buffer, unsigned long long *input, unsigned long long *tags, int sectors, TimeStamp *timestamps, int timestampCount);

int viBufReset(ViBuf *buffer);

int decBs0(VideoDec *decoder);

int viBufFlush(ViBuf *buffer);

// Copies the source bytes into the free space of a two-part ring buffer, returning the number of bytes written.
int cpy2area(unsigned char *first, int firstSize, unsigned char *second, int secondSize,
             unsigned char *source, int sourceSize, unsigned char *unused, int unusedSize);

#endif
