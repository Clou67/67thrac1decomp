#include "common.h"
#include "freeze.h"
#include "draw.h"
#include "fastfunc.h"
#include "font.h"
#include "gsregs.h"
#include "help.h"
#include "hud.h"
#include "memcard.h"
#include "pause.h"
#include "vuchain.h"

#define SAVE_DIALOG_MAX_SIZE 0x20000

// Level select map.
#define LEVEL_MARKER_COUNT 20
#define MAP_WIDTH 0x200
#define MAP_HEIGHT_NTSC 0x1A0
#define MAP_HEIGHT_PAL 0x1C0
#define MAP_TEXTURE 0xE99A
#define MAP_FRAME_MARKER 0xC
#define MAP_FRAME_SELECTION 0xD
#define MAP_FRAME_BACKGROUND 0xE
#define MAP_FRAME_CLOUDS 0xF
#define MAP_CLOUD_SCROLL_MASK 0xFFF
#define MAP_ALPHA_OPAQUE 0x80
#define MAP_ALPHA_BLEND 0x8000000044UL
#define MAP_ATEST 0x4B
#define MAP_BLACK 0x80000000
#define MAP_LABEL_COLOR 0x80F0F0F0
#define MAP_BLINK_ON_FRAMES 0x16
#define MAP_BLINK_OFF_FRAMES 8
#define MAP_LINE_GAP 8000

enum map_level_state {
    MAP_LEVEL_LOCKED,
    MAP_LEVEL_UNLOCKED = 2,
    MAP_LEVEL_VISITED
};

int MediumFontHeight = 17;

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/freeze", GetFreezePrevGameMode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/freeze", DisplayPrompt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/freeze", DrawDialogText);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/freeze", UpdateFreeze);

int GetSaveDialogRect(unsigned int size, void **first, void **second)
{
    if (size > SAVE_DIALOG_MAX_SIZE) {
        *first = 0;
        *second = 0;
        return -1;
    }

    *first = MemSlots.vu1_chain[0] + vu1_bufSize - size;
    *second = MemSlots.vu1_chain[1] + vu1_bufSize - size;

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/freeze", DrawMessageBox);
