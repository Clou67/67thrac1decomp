#include "common.h"
#include "framebuf.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", SetupFS_AA_buffer);

void SetBackgroundColor(int red, int green, int blue)
{
    aaClearRegs[AA_CLEAR_REGS_RGBAQ] = (long)red | ((long)green << 8) | ((long)blue << 16) | 0x80000000L;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", PutDispBuffer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", PutDrawBufferLarge);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", ClearDrawBufferLarge);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", PutDrawBufferSmall);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", SetMovieDrawSmallVIFChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", AA_BlurPass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", AA_DisplayPass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", DrawLineList);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/framebuf", DrawFilledRectGS);
