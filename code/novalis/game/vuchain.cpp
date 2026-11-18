#include "common.h"
#include "vuchain.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU0_loadMicroProgram);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_setBufSizeByLevel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_initChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_swapChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_sendChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_syncChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_addDataRef);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B4818);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_addDataDirect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B48C8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", VU1_addVIFcode);

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
    unsigned int *chainHead = vu1_bufPtr;
    unsigned int *packet = chainHead;

    chainHead += 4;
    vu1_bufPtr = chainHead;

    packet[0] = command + 0x90000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vuchain", func_002B5148);
