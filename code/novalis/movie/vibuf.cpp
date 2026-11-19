#include "common.h"
#include "videodec.h"

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", scTag2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufCreate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufReset__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufBeginPut__FP5ViBufPPUcPiT1T2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufEndPut__FP5ViBufi);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufAddDMA__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufStopDMA__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufRestartDMA__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufDelete__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufCount__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufFlush__FP5ViBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufModifyPts__FP5ViBufP9TimeStamp);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufPutTs__FP5ViBufP9TimeStamp);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufGetTs__FP5ViBufP9TimeStamp);
