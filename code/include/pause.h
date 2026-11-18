#ifndef PAUSE_H
#define PAUSE_H

extern int pauseActionListMode;

// State of the pause menu's map page; only the level being shown is known so far.
struct MapPageState {
    char unk0[0x224];
    int level;
};

extern MapPageState MapPage;

#endif
