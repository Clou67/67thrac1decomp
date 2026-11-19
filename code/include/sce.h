#ifndef SCE_H
#define SCE_H

// Sony SDK (libdma, libgraph, kernel). These libraries are C, so they keep C linkage.

struct sceDmaChan {
    unsigned int chcr;
};

// GS image transfer packets built by libgraph (96 and 112 bytes).
struct sceGsLoadImage {
    unsigned long data[12];
};

struct sceGsStoreImage {
    unsigned long data[14];
};

// libgraph register images (Sony libgraph.h layouts).
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct SifDmaTransfer {
    void *source;
    void *destination;
    int size;
    int attributes;
};

struct sceCdRMode {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
};

struct sceCdCLOCK {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
};

struct sceGsZbuf {
    unsigned long ZBP : 9;
    unsigned long pad09 : 15;
    unsigned long PSM : 4;
    unsigned long pad28 : 4;
    unsigned long ZMSK : 1;
    unsigned long pad33 : 31;
};

struct sceGsFrame {
    unsigned long FBP : 9;
    unsigned long pad09 : 7;
    unsigned long FBW : 6;
    unsigned long pad22 : 2;
    unsigned long PSM : 6;
    unsigned long pad30 : 2;
    unsigned long FBMSK : 32;
};

struct sceGsDispfb {
    unsigned long FBP : 9;
    unsigned long FBW : 6;
    unsigned long PSM : 5;
    unsigned long pad20 : 12;
    unsigned long DBX : 11;
    unsigned long DBY : 11;
    unsigned long pad54 : 10;
};

struct sceGsDispEnv {
    unsigned long pmode;
    unsigned long smode2;
    sceGsDispfb dispfb;
    unsigned long display;
    unsigned long bgcolor;
};

struct sceGsDrawEnv1 {
    sceGsFrame frame1;
    unsigned long frame1addr;
    sceGsZbuf zbuf1;
    unsigned long zbuf1addr;
    unsigned long xyoffset1;
    unsigned long xyoffset1addr;
    unsigned long scissor1;
    unsigned long scissor1addr;
    unsigned long prmodecont;
    unsigned long prmodecontaddr;
    unsigned long colclamp;
    unsigned long colclampaddr;
    unsigned long dthe;
    unsigned long dtheaddr;
    unsigned long test1;
    unsigned long test1addr;
};

struct sceGifTag {
    unsigned long NLOOP : 15;
    unsigned long EOP : 1;
    unsigned long pad16 : 16;
    unsigned long id : 14;
    unsigned long PRE : 1;
    unsigned long PRIM : 11;
    unsigned long FLG : 2;
    unsigned long NREG : 4;
    unsigned long REGS0 : 4;
    unsigned long REGS1 : 4;
    unsigned long REGS2 : 4;
    unsigned long REGS3 : 4;
    unsigned long REGS4 : 4;
    unsigned long REGS5 : 4;
    unsigned long REGS6 : 4;
    unsigned long REGS7 : 4;
    unsigned long REGS8 : 4;
    unsigned long REGS9 : 4;
    unsigned long REGS10 : 4;
    unsigned long REGS11 : 4;
    unsigned long REGS12 : 4;
    unsigned long REGS13 : 4;
    unsigned long REGS14 : 4;
    unsigned long REGS15 : 4;
} __attribute__((aligned(16)));

// Sony libgraph.h register value builder.
#define SCE_GS_SET_ZBUF(zbp, psm, zmsk) ((unsigned long)(zbp) | ((unsigned long)(psm) << 24) | ((unsigned long)(zmsk) << 32))

extern "C" {
int sceCdRead(unsigned int sector, unsigned int sectors, void *destination, sceCdRMode *mode);
int sceCdSync(int mode);
int sceCdReadClock(sceCdCLOCK *clock);
int sceScfGetLocalTimefromRTC(sceCdCLOCK *clock);
void FlushCache(int operation);
int sceSifSetDma(SifDmaTransfer *transfer, int count);
int sceSifDmaStat(int id);
int DIntr(void);
int EIntr(void);
int GetThreadId(void);
int ChangeThreadPriority(int thread, int priority);

sceDmaChan *sceDmaGetChan(int channel);
void sceDmaSend(sceDmaChan *channel, void *tag);

int sceGsSetDefLoadImage(sceGsLoadImage *image, short bp, short bw, short psm, short x, short y, short w, short h);
int sceGsSetDefStoreImage(sceGsStoreImage *image, short bp, short bw, short psm, short x, short y, short w, short h);
int sceGsExecStoreImage(sceGsStoreImage *image, void *destination);
int sceGsSyncPath(int mode, unsigned short timeout);
void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy);
void sceGsSetDefDrawEnv(sceGsDrawEnv1 *draw, short psm, short w, short h, short ztest, short zpsm);
void sceGsPutDispEnv(sceGsDispEnv *disp);
int sceGsPutDrawEnv(sceGifTag *giftag);

int AddDmacHandler(int channel, int (*handler)(int), int next);
int RemoveDmacHandler(int channel, int handlerId);
int EnableDmac(int channel);
int DisableDmac(int channel);
}

#endif
