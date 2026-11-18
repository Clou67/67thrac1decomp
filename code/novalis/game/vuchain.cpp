#include "common.h"
#include "vuchain.h"

volatile int VifChainFlags = 0;

void VU0_loadMicroProgram(long *data)
{
    while (*D0_CHCR & D_CHCR_STR) {
        FastSitAndSpin(16);
    }

    *D0_QWC = 0;
    *D0_TADR = (unsigned int)data & 0x0FFFFFFF;
    *D0_CHCR = 0x145;

    while (*D0_CHCR & D_CHCR_STR) {
        FastSitAndSpin(16);
    }
}


void VU1_setBufSizeByLevel(void)
{
    int level = Level;

    if (level >= LEVEL_COUNT) {
        level = 0;
    }

    vu1_bufSize = vu1_buf_table[level];
}

void VU1_initChain(void)
{
    vu1_DmaBuffers[0] = MemSlots.vu1_chain[0];
    vu1_DmaBuffers[1] = MemSlots.vu1_chain[1];
    vu1_bufId = 0;
    vu1_bufPtr = vu1_DmaBuffers[0];

    EngScratchPad = vu1_bufPtr + vu1_bufSize - EngScratchPadSize;
    SkinVertexCache = EngScratchPad - SKIN_VERTEX_CACHE_SIZE;
}


void VU1_swapChain(void)
{
    vu1_bufId = 1 - vu1_bufId;
    vu1_chainEnd = vu1_bufPtr;
    vu1_bufPtr = vu1_DmaBuffers[vu1_bufId];

    EngScratchPad = vu1_bufPtr + vu1_bufSize - EngScratchPadSize;
    SkinVertexCache = EngScratchPad - SKIN_VERTEX_CACHE_SIZE;
}


void VU1_sendChain(void)
{
    int overflow = 0;
    int used;

    VifChainFlags |= VIF_CHAIN_ALL_STAGES;
    used = vu1_bufPtr - vu1_DmaBuffers[vu1_bufId];

    if (used > vu1_bufMaxUsed) {
        vu1_bufMaxUsed = used;

        if (used > vu1_bufSize) {
            printf_stub("vu1 chain overflow\n");
            overflow = 1;
        }
    }

    if (!overflow) {
        sceDmaChan *channel;

        VU1_CHAIN_WORD(0) = DMA_TAG_END;
        VU1_CHAIN_WORD(4) = 0;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = 0;

        channel = sceDmaGetChan(DMA_CHANNEL_VIF1);
        channel->chcr |= 0xC0;
        FlushCache(0);
        sceDmaSend(channel, vu1_DmaBuffers[vu1_bufId]);
        return;
    }

    VifChainFlags = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_syncChain);


void VU1_addDataRef(void *data, int qcnt)
{
    VU1_CHAIN_WORD(0) = qcnt | DMA_TAG_REF;
    VU1_CHAIN_WORD(4) = (unsigned int)data;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = 0;

    vu1_bufPtr += 16;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B4818);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_addDataDirect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B48C8);


void VU1_addVIFcode(unsigned int vifcode)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_CNT;
    VU1_CHAIN_WORD(4) = 0;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = vifcode;

    vu1_bufPtr += 16;
}


void VU1_addGSregister(unsigned int reg, unsigned long value)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_CNT | 2;
    VU1_CHAIN_WORD(4) = 0;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 2;

    VU1_CHAIN_WORD(16) = GIF_TAG_AD_LOW;
    VU1_CHAIN_WORD(20) = GIF_TAG_AD_HIGH;
    VU1_CHAIN_WORD(24) = GIF_REG_AD;
    VU1_CHAIN_WORD(28) = 0;

    VU1_CHAIN_DWORD(32) = value;
    VU1_CHAIN_WORD(40) = reg;
    VU1_CHAIN_WORD(44) = 0;

    vu1_bufPtr += 48;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B49D0);


void VU1_setScissor(int left, int right, int top, int bottom)
{
    int maxX = occlViewParams[0] - 1;
    int maxY = occlViewParams[1] - 1;

    VU1_CHAIN_WORD(0) = DMA_TAG_CNT | 2;
    VU1_CHAIN_WORD(4) = 0;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 2;

    if (right > maxX) {
        right = maxX;
    }

    if (left < 0) {
        left = 0;
    }

    if (top < 0) {
        top = 0;
    }

    if (bottom > maxY) {
        bottom = maxY;
    }

    VU1_CHAIN_WORD(16) = GIF_TAG_AD_LOW;
    VU1_CHAIN_WORD(20) = GIF_TAG_AD_HIGH;
    VU1_CHAIN_WORD(24) = GIF_REG_AD;
    VU1_CHAIN_WORD(28) = 0;

    VU1_CHAIN_DWORD(32) = (unsigned long)left | ((unsigned long)right << 16)
                                         | ((unsigned long)top << 32) | ((unsigned long)bottom << 48);
    VU1_CHAIN_WORD(40) = GS_REG_SCISSOR_1;
    VU1_CHAIN_WORD(44) = 0;

    vu1_bufPtr += 48;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B4AF8);


void VU1_texFlush(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 3;
    VU1_CHAIN_WORD(4) = (unsigned int)Gif_Tex_Flush;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 3;

    vu1_bufPtr += 16;
}


void VU1_gsRegsNormal(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 3;
    VU1_CHAIN_WORD(4) = (unsigned int)vu1GsRegsNormal;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 3;

    vu1_bufPtr += 16;
}


void VU1_gsRegsEffects(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 3;
    VU1_CHAIN_WORD(4) = (unsigned int)vu1GsRegsEffects;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 3;

    vu1_bufPtr += 16;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B4C20);


void VU1_gsRegsFont(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 11;
    VU1_CHAIN_WORD(4) = (unsigned int)vu1GsRegsFont;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 11;

    vu1_bufPtr += 16;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", StashGSMem);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", UploadGSMemLinear);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", DMAC_VIF1_Enable);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", DMAC_VIF1_Disable);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", DMAC_VIF1_Handler);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", DMAC_BEIS_Handler);

// Appends a VIF1 command packet (command word plus three zero words) to the VU1 chain.
void Vif1ChainCmd(int command)
{
    unsigned char *chainHead = vu1_bufPtr;
    unsigned int *packet = (unsigned int *)chainHead;

    chainHead += 16;
    vu1_bufPtr = chainHead;

    packet[0] = command + VIF_CHAIN_CMD;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B5148);
