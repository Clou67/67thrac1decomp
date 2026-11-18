#include "common.h"
#include "memcard.h"
#include "fastfunc.h"
#include "libc.h"
#include "wad.h"
#include "help.h"
#include "music.h"
#include "vuchain.h"
#include "mcstate.h"
#include "map.h"
#include "pause.h"

#define CURRENT_CARD g_memcard.memcards[g_memcard.slot]

// Save chunks whose data differed from what was already in memory on the last restore.
int g_loaderr = 0;

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

TEXT_PADDING(0x27BD0060, 0x00000000);

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

int memcard_GetDataSize(mc_data *mcd)
{
    int size = 8;

    for (; mcd->addr != 0; mcd++) {
        size += 8;
        size += mcd->size;
        size = (size + 3) & ~3;
    }

    return size + 8;
}

int memcard_Checksum(char *data, int size)
{
    unsigned char *byte = (unsigned char *)data;
    unsigned char *end;
    unsigned int crc;

    if (size > MEMCARD_CHECKSUM_LIMIT) {
        return 0;
    }

    end = byte + size;
    crc = 0xEDB88320;

    while (byte < end) {
        crc ^= *byte++ << 8;

        for (int bit = 7; bit >= 0; bit--) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1F45;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc & 0xFFFF;
}

int memcard_TestChecksum(char *addr)
{
    int checksum = *(int *)(addr + 4);
    int good = 0;
    int size = *(int *)addr;

    if (checksum != 0) {
        good = memcard_Checksum(addr + 8, size) == checksum;
    }

    return good;
}

int memcard_PrepData(char *addr, int index, mc_data *mcd)
{
    int *cursor = (int *)(addr + 8);
    int size = 0;

    if (mcd->addr != 0) {
        mc_data *entry = mcd;

        do {
            char *source = (char *)entry->addr + index * entry->size;

            size += 8;
            cursor[0] = entry->iff;
            cursor[1] = entry->size;
            cursor += 2;
            FastMemCopy32(cursor, source, entry->size);

            cursor = (int *)((char *)cursor + entry->size);
            size += entry->size;
            cursor = (int *)(((int)cursor + 3) & ~3);
            size = (size + 3) & ~3;
            entry++;
        } while (entry->addr != 0);
    }

    cursor[1] = 0;
    cursor[0] = -1;

    size += 8;
    *(int *)(addr + 4) = memcard_Checksum(addr + 8, size);
    *(int *)addr = size;

    return size + 8;
}

void memcard_RestoreInfo(char *addr, int slot, int index)
{
    g_memcard.memcards[slot].info[index].bad = !memcard_TestChecksum(addr);

    // Each value sits in its own save chunk: 8 bytes of chunk header, then the int.
    addr += 0x10;
    g_memcard.memcards[slot].info[index].level = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].bolts = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].completes = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].elapsedTime = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].saveTime = *(sceCdCLOCK *)addr;
}

int memcard_RestoreData(char *addr, int index, mc_data *mcd)
{
    int errors;
    int restored;
    int entryIndex;

    if (!memcard_TestChecksum(addr)) {
        return 1;
    }

    addr += 8;
    errors = 0;
    restored = 8;

    for (entryIndex = 0; mcd[entryIndex].addr != 0; entryIndex++) {
        mcd[entryIndex].mark = 0;
    }

    while (((mc_chunk *)addr)->iff != -1) {
        mc_chunk *chunk = (mc_chunk *)addr;
        mc_data *entry;

        entryIndex = 0;

        if (mcd[0].addr == 0) {
            goto missing;
        }

        while (mcd[entryIndex].iff != chunk->iff) {
            entryIndex++;

            if (mcd[entryIndex].addr == 0) {
                goto missing;
            }
        }

        entry = (mc_data *)(entryIndex * (int)sizeof(mc_data) + (int)mcd);

        if (entry->addr != 0) {
            int chunkSize = chunk->size;
            char *destination = (char *)entry->addr + index * entry->size;
            int size;

            if (chunkSize == entry->size) {
                size = entry->size;
                entry->mark = 1;
            } else if (chunkSize < entry->size) {
                size = chunkSize;
                entry->mark = -1;
            } else {
                size = entry->size;
                entry->mark = -2;
            }

            if (memcmp(destination, chunk + 1, size) != 0) {
                g_loaderr++;
            }

            FastMemCopy32(destination, chunk + 1, size);
            restored += ((size + 3) & ~3) + 8;
        } else {
        missing:
            errors++;
        }

        addr += ((chunk->size + 3) & ~3) + 8;
    }

    restored += 8;

    if (restored != memcard_GetDataSize(mcd)) {
        errors++;
    }

    // The terminating chunk is followed by the id of the last block that was saved.
    addr += 8;

    for (entryIndex = 0; mcd[entryIndex].addr != 0 && mcd[entryIndex].iff != *(int *)addr; entryIndex++) {
        if (mcd[entryIndex].mark <= 0) {
            errors++;
        }
    }

    g_memcard.memcards[g_memcard.slot].oldsave = errors;

    return errors;
}

int memcard_Save(int force, int level)
{
    sceCdReadClock(&LastSaveTime);
    sceScfGetLocalTimefromRTC(&LastSaveTime);
    map_SaveLevelObjectState();
    map_SaveRevealMask(&MapRevealMasks[Level * MAP_REVEAL_MASK_SIZE]);

    if (g_memcard.useslot == -1 || g_memcard.memcards[g_memcard.useslot].saveslot < 0) {
        return force == 0;
    }

    g_memcard.autosave |= force;

    if (g_memcard.autosave != 0) {
        if (force == 0) {
            mcstate_flags |= MCSTATE_FLAG_DO_SAVE;
        }

        if (g_memcard.stage < MC_STAGE_FORMAT && g_memcard.nextstage < 0) {
            unsigned char visited = 0;

            g_memcard.level = Level;

            if (level >= 0) {
                Level = level;
                visited = LevelVisited[level];

                if (!visited) {
                    LevelVisited[level] = 1;
                }
            }

            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].bolts = HeroBolts;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].level = Level;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].elapsedTime = ElapsedTime;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].saveTime = LastSaveTime;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].completes = GameCompleted;

            memcard_PrepData(mc_gameprepbuff, 0, mc_gamedata);
            memcard_PrepData(mc_levelprepbuff, g_memcard.level, mc_leveldata);

            if (level >= 0) {
                LevelVisited[Level] = visited;
                Level = g_memcard.level;
            }

            if (g_memcard.nextstage < 0) {
                g_memcard.nextstage = MC_STAGE_SAVE;
                g_memcard.nextslot = g_memcard.useslot;
            }
        }
    }

    return g_memcard.nextstage == MC_STAGE_SAVE;
}
