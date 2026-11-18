#include "common.h"
#include "framebuf.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", SetupFS_AA_buffer);

void SetBackgroundColor(int red, int green, int blue)
{
    aaClearRegs[AA_CLEAR_REGS_RGBAQ] = (long)red | ((long)green << 8) | ((long)blue << 16) | 0x80000000L;
}

void PutDispBuffer(void)
{
    sceGsPutDispEnv(&pAAbuff->disp);
}

void PutDrawBufferLarge(void)
{
    if (vu1_bufPtr != 0) {
        VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DRAW_ENV_QWC;
        VU1_CHAIN_WORD(4) = (unsigned int)&pAAbuff->giftagDrawLarge & EE_PHYSICAL_ADDRESS_MASK;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DRAW_ENV_QWC;

        vu1_bufPtr += 16;
    } else {
        sceGsPutDrawEnv(&pAAbuff->giftagDrawLarge);
    }
}

void ClearDrawBufferLarge(int black)
{
    if (vu1_bufPtr != 0) {
        VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_CLEAR_REGS_QWC;
        VU1_CHAIN_WORD(4) = (unsigned int)aaClearRegs;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_CLEAR_REGS_QWC;

        vu1_bufPtr += 16;
    }
}

void PutDrawBufferSmall(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DRAW_ENV_QWC;
    VU1_CHAIN_WORD(4) = (unsigned int)&pAAbuff->giftagDrawSmall & EE_PHYSICAL_ADDRESS_MASK;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DRAW_ENV_QWC;

    vu1_bufPtr += 16;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", SetMovieDrawSmallVIFChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", AA_BlurPass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", AA_DisplayPass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", DrawLineList);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", DrawFilledRectGS);
