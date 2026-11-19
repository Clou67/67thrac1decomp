#ifndef HERO_H
#define HERO_H

#include "moby.h"

#define HERO_NO_HUD_HANDLE -1
#define HERO_SHIP_FLAG_RESET 0x1
#define HERO_RACE_LAP_COUNT 3
#define HERO_RACE_MOBY_LAP_OFFSET 0xBC

// Only the fields the freeze mode touches are known so far.
struct HeroState {
    char unk0[0x80];
    Vec4 pos;
    // z is the yaw.
    Vec4 rot;
    char unkA0[0xFC];
    int controlModeTimer;
    char unk1A0[0x6E0];
    int trickHudHandle;
    char unk884[0xC];
    unsigned char *raceMoby;
    int raceTimeFrames;
    short racePathNode;
    short raceLap;
    char unk89C[0xC];
    int raceScore;
    char unk8AC[0x14];
    int racePosition;
    char unk8C4[0xD4B];
    unsigned char shipFlags;
    char unk1610[0x6F0];
    float savedPosRot[8];
    char unk1D20[0x360];
    MobyInstance *moby;
    int state;
    char unk2088[0x220];
    int health;
};

// Hero states.
#define HERO_STATE_VISIBOMB_CONTROL 29

extern HeroState Hero;

// Item ids (weapons, gadgets and upgrades).
enum item_id {
    ITEM_HELI_PACK = 2,
    ITEM_THRUSTER_PACK,
    ITEM_HYDRO_PACK,
    ITEM_SONIC_SUMMONER,
    ITEM_O2_MASK,
    ITEM_PILOTS_HELMET,
    ITEM_WRENCH,
    ITEM_SUCK_CANNON,
    ITEM_BOMB_GLOVE,
    ITEM_DEVASTATOR,
    ITEM_SWINGSHOT,
    ITEM_VISIBOMB_GUN,
    ITEM_TAUNTER,
    ITEM_BLASTER,
    ITEM_PYROCITOR,
    ITEM_MINE_GLOVE,
    ITEM_WALLOPER,
    ITEM_TESLA_CLAW,
    ITEM_GLOVE_OF_DOOM,
    ITEM_MORPH_O_RAY,
    ITEM_HYDRODISPLACER,
    ITEM_RYNO,
    ITEM_DRONE_DEVICE,
    ITEM_DECOY_GLOVE,
    ITEM_TRESPASSER,
    ITEM_METAL_DETECTOR,
    ITEM_MAGNEBOOTS,
    ITEM_GRINDBOOTS,
    ITEM_HOVERBOARD,
    ITEM_HOLOGUISE,
    ITEM_PDA,
    ITEM_MAP_O_MATIC,
    ITEM_BOLT_GRABBER,
    ITEM_PERSUADER,

    ITEM_COUNT = 37
};

// Items the hero has, and items picked up at least once (picking one up again shows a different message).
extern unsigned char UnlockableItems[ITEM_COUNT];
extern unsigned char ObtainedItems[ITEM_COUNT];

// The equipped item first, then the items equipped before it.
extern int EquippedItems[4];

#define QUICK_SELECT_SLOT_COUNT 8
extern int QuickSelectItems[QUICK_SELECT_SLOT_COUNT];

void Hero_RevertToRatchet(void);
void Hero_Warp(float *position, float *rotation, int flags, int snap);

#endif
