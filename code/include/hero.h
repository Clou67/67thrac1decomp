#ifndef HERO_H
#define HERO_H

#include "moby.h"

#define HERO_NO_HUD_HANDLE -1
#define HERO_SHIP_FLAG_RESET 0x1
#define HERO_RACE_LAP_COUNT 3
#define HERO_RACE_MOBY_LAP_OFFSET 0xBC

// Only the fields the freeze mode touches are known so far.
struct HeroState {
    char unk0[0x19C];
    int controlModeTimer;
    char unk1A0[0x6E0];
    int trickHudHandle;
    char unk884[0xC];
    unsigned char *raceMoby;
    char unk894[6];
    short raceLap;
    char unk89C[0xD73];
    unsigned char shipFlags;
    char unk1610[0x6F0];
    float savedPosRot[8];
    char unk1D20[0x360];
    MobyInstance *moby;
};

extern HeroState Hero;

void Hero_RevertToRatchet(void);
void Hero_Warp(float *position, float *rotation, int flags, int snap);

#endif
