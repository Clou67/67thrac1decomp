#ifndef PAUSE_H
#define PAUSE_H

struct MobyInstance;

extern int pauseActionListMode;

// State of the pause menu's map page; only the level being shown is known so far.
struct MapPageState {
    char unk0[0x224];
    int level;
};

extern MapPageState MapPage;
extern int pauseActionList[];

int MenuText_OnEnterResetBuffers(void);

void ItemView_SpinMobyUpdate(MobyInstance *moby);

#endif
