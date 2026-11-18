#include "common.h"
#include "vuchain.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU0_loadMicroProgram);


void VU1_setBufSizeByLevel(void)
{
    int level = currentLevelId;

    if (level >= LEVEL_COUNT) {
        level = 0;
    }

    vu1_bufSize = vu1_buf_table[level];
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_initChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_swapChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_sendChain);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_addGSregister);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B49D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_setScissor);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B4AF8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_texFlush);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_gsRegsNormal);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_gsRegsEffects);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B4C20);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_gsRegsBlock_13cf10);

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
