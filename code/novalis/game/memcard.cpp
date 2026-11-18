#include "common.h"
#include "memcard.h"
#include "fastfunc.h"
#include "libc.h"
#include "wad.h"
#include "help.h"
#include "music.h"
#include "vuchain.h"

void memcard_GetName(char *buff)
{
    int position;
    unsigned char region = buff[0x12];

    if (region == 'E') {
        SAVEGAME_NAME[2] = region;
    }

    for (position = 3; position < 7; position++) {
        SAVEGAME_NAME[position] = buff[position + 0xD];
    }

    for (position = 8; position < 11; position++) {
        SAVEGAME_NAME[position] = buff[position + 0xD];
    }

    for (position = 11; position < 13; position++) {
        SAVEGAME_NAME[position] = buff[position + 0xE];
    }

    strncpy(SAVEGAME_WILD, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_SYS, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_VIEW, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_MAIN, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_MAIN + 0x14, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_SLOT, SAVEGAME_NAME, 13);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", func_0025F560);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_RestoreGame);

void memcard_ResetGame(void)
{
    void *saveBuffer;
    void *secondBuffer;

    GetSaveDialogRect(bootAssets.savegame.length << 11, &saveBuffer, &secondBuffer);
    music_Sync(1);
    music_LoadFileSync(saveBuffer, bootAssets.savegame.offset, bootAssets.savegame.length);
    memcard_RestoreGame((char *)saveBuffer + *(int *)((char *)saveBuffer + 0x10));
    Level = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_Update);

void memcard_MakeWholeSave(char *addr)
{
    *(int *)addr = memcard_GetDataSize(mc_gamedata);
    *(int *)(addr + 4) = memcard_GetDataSize(mc_leveldata);

    addr += 8;
    addr += memcard_PrepData(addr, 0, mc_gamedata);

    for (int level = 0; level < MEMCARD_LEVEL_COUNT; level++) {
        addr += memcard_PrepData(addr, level, mc_leveldata);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_Init);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_GetDataSize);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_Checksum);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_TestChecksum);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_PrepData);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_RestoreInfo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_RestoreData);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/memcard", memcard_Save);
