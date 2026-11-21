#include "common.h"
#include "framebuf.h"
#include "music.h"
#include "wad.h"

extern unsigned char debugFontBuffer[] __attribute__((section(".data")));
extern unsigned long long debugFontPifHeader;

void LoadPifAsPSMT8H(unsigned char *source, unsigned char *destination, int textureAddress, int paletteAddress);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/bloaders", LoadPifAsPSMT8H);

void LoadDebugFont(void)
{
    unsigned char pifBuffer[0x18];

    music_LoadFileSync(debugFontBuffer, bootAssets.debugFont.offset, bootAssets.debugFont.length);
    LoadPifAsPSMT8H(debugFontBuffer, pifBuffer, GSmemZbuf + 0xC0000, 0x3FFC00);
    debugFontPifHeader = *(unsigned long long *)pifBuffer;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/bloaders", func_0020CC70);
