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

// Sony eekernel.h: interrupt handlers return through sync.l; ei.
#define ExitHandler() asm volatile("sync.l; ei")

extern "C" {
void FlushCache(int operation);

sceDmaChan *sceDmaGetChan(int channel);
void sceDmaSend(sceDmaChan *channel, void *tag);

int sceGsSetDefLoadImage(sceGsLoadImage *image, short bp, short bw, short psm, short x, short y, short w, short h);
int sceGsSetDefStoreImage(sceGsStoreImage *image, short bp, short bw, short psm, short x, short y, short w, short h);
int sceGsExecStoreImage(sceGsStoreImage *image, void *destination);
int sceGsSyncPath(int mode, unsigned short timeout);

int AddDmacHandler(int channel, int (*handler)(int), int next);
int RemoveDmacHandler(int channel, int handlerId);
int EnableDmac(int channel);
int DisableDmac(int channel);
}

#endif
