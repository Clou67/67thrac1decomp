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
    if (vu1_bufPtr.bytes != 0) {
        VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DRAW_ENV_QWC;
        VU1_CHAIN_WORD(4) = (unsigned int)&pAAbuff->giftagDrawLarge & EE_PHYSICAL_ADDRESS_MASK;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DRAW_ENV_QWC;

        vu1_bufPtr.bytes += 16;
    } else {
        sceGsPutDrawEnv(&pAAbuff->giftagDrawLarge);
    }
}

void ClearDrawBufferLarge(int black)
{
    if (vu1_bufPtr.bytes != 0) {
        VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_CLEAR_REGS_QWC;
        VU1_CHAIN_WORD(4) = (unsigned int)aaClearRegs;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_CLEAR_REGS_QWC;

        vu1_bufPtr.bytes += 16;
    }
}

void PutDrawBufferSmall(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DRAW_ENV_QWC;
    VU1_CHAIN_WORD(4) = (unsigned int)&pAAbuff->giftagDrawSmall & EE_PHYSICAL_ADDRESS_MASK;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DRAW_ENV_QWC;

    vu1_bufPtr.bytes += 16;
}

void SetMovieDrawSmallVIFChain(int widthLog2, int heightLog2, int gsAddress)
{
    int bufferWidthLog2 = widthLog2 - 6;
    long *gifTag;
    sceGsDrawEnv1 *drawEnv;
    long *clearSprite;

    if (bufferWidthLog2 <= 0) {
        bufferWidthLog2 = 1;
    }

    aaBuff.auxFBP = gsAddress >> 13;
    aaBuff.auxW = 1 << widthLog2;
    aaBuff.auxH = 1 << heightLog2;
    AuxBufferTex0 = (unsigned long)(gsAddress >> 8) | ((unsigned long)(1 << bufferWidthLog2) << 14)
                  | ((unsigned long)widthLog2 << 26) | ((unsigned long)heightLog2 << 30) | (1UL << 34);

    FastMemSetZero(vu1_bufPtr.words, 0xF0);

    vu1_bufPtr.words[0] = DMA_TAG_CNT | 0xE;
    vu1_bufPtr.words[1] = 0;
    vu1_bufPtr.words[2] = 0;
    vu1_bufPtr.words[3] = VIF_DIRECT | 0xE;
    vu1_bufPtr.words += 4;

    gifTag = (long *)vu1_bufPtr.words;
    gifTag[0] = 0x1000000000000008L;
    gifTag[1] = GIF_REG_AD;
    vu1_bufPtr.words += 4;

    drawEnv = (sceGsDrawEnv1 *)vu1_bufPtr.words;
    sceGsSetDefDrawEnv(drawEnv, aaBuff.auxPSM, aaBuff.auxW, aaBuff.auxH, 3, 0);
    drawEnv->frame1.FBP = aaBuff.auxFBP;
    drawEnv->zbuf1 = SCE_GS_SET_ZBUF(aaBuff.zFBP, aaBuff.zPSM & 0xF, 0);
    vu1_bufPtr.words += sizeof(sceGsDrawEnv1) / 4;

    clearSprite = (long *)vu1_bufPtr.words;
    clearSprite[0] = 0x1000000000000001L;
    clearSprite[1] = GIF_REG_AD;
    clearSprite[2] = 0x30003;
    clearSprite[3] = 0x47;
    clearSprite[4] = 0x4400000000008001L;
    clearSprite[5] = 0x4410;
    clearSprite[6] = 0x106;
    clearSprite[7] = 0;
    clearSprite[8] = (long)(0x8000 - aaBuff.auxW * 8) | ((long)(0x8000 - aaBuff.auxH * 8) << 16);
    clearSprite[9] = (long)(aaBuff.auxW * 8 + 0x8000) | ((long)(aaBuff.auxH * 8 + 0x7FF0) << 16);
    vu1_bufPtr.words += 0x14;
}

void AA_BlurPass(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_BLUR_REGS_QWC;
    VU1_CHAIN_WORD(4) = (unsigned int)aaBlurRegs;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_BLUR_REGS_QWC;

    vu1_bufPtr.bytes += 16;
}

void AA_DisplayPass(int opaque)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DISPLAY_REGS_QWC;
    VU1_CHAIN_WORD(4) = (unsigned int)aaDisplayRegs;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DISPLAY_REGS_QWC;

    vu1_bufPtr.bytes += 16;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", DrawLineList);

void DrawFilledRectGS(int x0, int y0, int x1, int y1, int width, int height, unsigned int color)
{
    DmaTag *tag;
    unsigned long *packet;
    int left;
    int top;
    int right;
    int bottom;

    VU1_addVIFcode(VIF_FLUSHA);
    VU1_addGSregister(GS_REG_ALPHA_1, 0x64);

    vu1_bufPtr.tag->tag = DMA_TAG_CNT | 6;
    vu1_bufPtr.tag->addr = 0;
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = VIF_DIRECT | 6;

    top = y0 << 4;
    bottom = y1 << 4;
    left = x0 << 4;
    right = x1 << 4;

    bottom += 0x8000;
    top += 0x8000;
    right += 0x8000;
    left += 0x8000;

    bottom -= height << 3;
    top -= height << 3;
    right -= width << 3;
    left -= width << 3;

    tag = vu1_bufPtr.tag;
    packet = (unsigned long *)(tag + 1);
    vu1_bufPtr.tag = tag + 1;

    packet[0] = 0x1000000000000001UL;
    packet[1] = GIF_REG_AD;
    packet[2] = 0x33003;
    packet[3] = 0x47;
    packet[4] = 0x2400000000000001UL;
    packet[5] = 0x10;
    packet[6] = 0x106;
    packet[7] = color;
    packet[8] = 0x2400000000008001UL;
    packet[9] = 0x44;
    packet[10] = left | ((unsigned long)top << 16);
    packet[11] = right | ((unsigned long)bottom << 16);
    vu1_bufPtr.bytes += 0x60;

    VU1_addGSregister(GS_REG_ALPHA_1, 0x8000000044UL);
    VU1_addVIFcode(VIF_FLUSHA);
}
