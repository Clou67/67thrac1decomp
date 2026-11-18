#ifndef MEMCARD_H
#define MEMCARD_H

// One memory card port. RC1 keeps much less per card than DL's memcard_data.
struct memcard_data {
    int port;
    int slot;
    int type;
    int free;
    int unk_10;
    int saveslot;
    int unk_18;
    int result;     // last sceMcGetInfo result: 0 same card, -1 new formatted card, -2 unformatted
    char unk_20[0x3C];
};

// Field names follow DL's memcard_globals.
struct memcard_globals {
    memcard_data memcards[2];
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

#endif
