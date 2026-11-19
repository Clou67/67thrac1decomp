#include "common.h"
#include "videodec.h"

void setD4_CHCR(unsigned int value);

enum {
    VIBUF_BLOCK_SHIFT = 11,
    VIBUF_BLOCK_SIZE = 1 << VIBUF_BLOCK_SHIFT,
    VIBUF_PHYSICAL_ADDRESS_MASK = 0x0FFFFFFF,
    IPU_OUTPUT_DMA_IDLE_CHCR = 5,
    IPU_OUTPUT_DMA_MADR = 0x1000B410,
    IPU_OUTPUT_DMA_QWC = 0x1000B420,
    IPU_OUTPUT_DMA_TADR = 0x1000B430
};

unsigned int getFIFOindex(ViBuf *buffer, void *position)
{
    unsigned int endTag = ((buffer->n << 4) + (unsigned int)buffer->tag + 0x10) & VIBUF_PHYSICAL_ADDRESS_MASK;
    if (position == (void *)endTag)
        return 0;
    return ((unsigned int)position - (unsigned int)buffer->data) >> VIBUF_BLOCK_SHIFT;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", setD3_CHCR__FUi);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", setD4_CHCR__FUi);

void scTag2(unsigned long *tag, unsigned int address, unsigned int id, unsigned int count)
{
    *tag = ((unsigned long)address << 32) | (((unsigned long)id << 32) >> 4) | (unsigned long)count;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufCreate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufReset__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufBeginPut__FP5ViBufPPUcPiT1T2);

void viBufEndPut(ViBuf *buffer, int size)
{
    WaitSema(buffer->sema);
    buffer->readBytes += size;
    buffer->totalBytes += size;
    SignalSema(buffer->sema);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufAddDMA__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufStopDMA__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufRestartDMA__FP5ViBuf);

int viBufDelete(ViBuf *buffer)
{
    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    *(volatile unsigned int *)IPU_OUTPUT_DMA_QWC = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_TADR = 0;
    DeleteSema(buffer->sema);
    return 1;
}

int viBufCount(ViBuf *buffer)
{
    WaitSema(buffer->sema);
    int count = (buffer->dmaN << VIBUF_BLOCK_SHIFT) + buffer->readBytes;
    SignalSema(buffer->sema);
    return count;
}

int viBufFlush(ViBuf *buffer)
{
    WaitSema(buffer->sema);
    int rounded = buffer->readBytes + (VIBUF_BLOCK_SIZE - 1);
    int adjusted = buffer->readBytes + (2 * VIBUF_BLOCK_SIZE - 2);
    int limit = -1;
    if (limit < rounded)
        adjusted = rounded;
    buffer->readBytes = (adjusted >> VIBUF_BLOCK_SHIFT) << VIBUF_BLOCK_SHIFT;
    return SignalSema(buffer->sema);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufModifyPts__FP5ViBufP9TimeStamp);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufPutTs__FP5ViBufP9TimeStamp);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufGetTs__FP5ViBufP9TimeStamp);
