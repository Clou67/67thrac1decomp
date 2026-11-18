#ifndef MEMCARD_H
#define MEMCARD_H

#include "sce.h"

#define MEMCARD_SAVE_SLOTS 5

// What the save menu shows for one save slot (DL memcard_saveinfo, without
// savedDifficultyLevel).
struct memcard_saveinfo {
    int level;
    int bolts;
    int completes;
    int elapsedTime;
    sceCdCLOCK saveTime;
    int bad;
};

// One memory card port (DL memcard_data, cut down for RC1).
struct memcard_data {
    int port;
    int slot;
    int type;
    int free;
    int unk_10;
    int saveslot;
    int unk_18;
    int result;     // last sceMcGetInfo result: 0 same card, -1 new formatted card, -2 unformatted
    memcard_saveinfo info[MEMCARD_SAVE_SLOTS];
    int oldsave;    // number of save chunks that didn't match the current layout
    int unk_B0;
    int unk_B4;
};

// One block of game state that goes into a save, listed in mc_gamedata and
// mc_leveldata. A table ends with a null addr.
struct mc_data {
    void *addr;
    int size;
    int iff;        // chunk id written in front of the data
    int mark;       // set by memcard_RestoreData: 1 same size, -1 shorter, -2 longer
};

// One chunk in a save block: its id, size, then the data.
struct mc_chunk {
    int iff;
    int size;
};

// Field names follow DL's memcard_globals.
struct memcard_globals {
    memcard_data memcards[1];
    int cmd;
    int res;
    int useslot;
    int slot;
    int level;
    int sync;
    int file;
    int stage;
    int substage;
    int nextstage;
    int nextslot;
    int err;
    int errslot;
    char *addr;
    int size;
    int autosave;
};

// Values of sceMcGetInfo's result, kept in memcard_data::result.
#define MC_RESULT_SAME_CARD 0
#define MC_RESULT_NEW_CARD -1
#define MC_RESULT_UNFORMATTED -2

// memcard_globals::stage / nextstage values.
#define MC_STAGE_IDLE 2
#define MC_STAGE_FORMAT 3
#define MC_STAGE_CHECK_SAVE 7
#define MC_STAGE_CREATE_SAVE 9

// Free space (in KB) a save needs.
#define MC_SAVE_SIZE 0x15E

extern memcard_globals g_memcard;
extern mc_data mc_gamedata[];
extern mc_data mc_leveldata[];

// Memory card paths, patched with the disc's product code by memcard_GetName.
extern char SAVEGAME_NAME[];
extern char SAVEGAME_WILD[];
extern char SAVEGAME_SYS[];
extern char SAVEGAME_VIEW[];
extern char SAVEGAME_MAIN[];
extern char SAVEGAME_SLOT[];

// Largest save block memcard_Checksum accepts.
#define MEMCARD_CHECKSUM_LIMIT 0x1800

// Number of levels with their own block in a whole save.
#define MEMCARD_LEVEL_COUNT 20

void memcard_GetName(char *buff);
void memcard_RestoreGame(char *addr);
void memcard_ResetGame(void);
void memcard_Update(void);
void memcard_MakeWholeSave(char *addr);
void memcard_Init(void);
int memcard_GetDataSize(mc_data *mcd);
int memcard_Checksum(char *data, int size);
int memcard_TestChecksum(char *addr);
int memcard_PrepData(char *addr, int index, mc_data *mcd);
void memcard_RestoreInfo(char *addr, int slot, int index);
int memcard_RestoreData(char *addr, int index, mc_data *mcd);
int memcard_Save(int flags, int slot);

#endif
