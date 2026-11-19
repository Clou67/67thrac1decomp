#include "common.h"
#include "fastfunc.h"
#include "moby.h"
#include "respawn.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/respawn", NAVG_AllocSlot);

struct CheckpointData {
    int set;
    unsigned char spawnState[0x4C];
    MobyVarList vars;
    unsigned char objectState[0x800];
    int musicTrack;
    unsigned char padding[8];
};

extern CheckpointData LiveCheckpoint;
extern CheckpointData CheckpointSet;
extern unsigned int CheckpointBits[64];

void ClearCheckpointData(void)
{
    FastMemSet(&LiveCheckpoint, 0, sizeof(LiveCheckpoint));
    FastMemSet(&CheckpointSet, 0, sizeof(CheckpointSet));
    FastMemSet(CheckpointBits, 0, sizeof(CheckpointBits));
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/respawn", SetSpawnPoint);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/respawn", RestoreCheckpoint);

extern MobyInstance *MobyInstances;
extern MobyInstance *MobyInstancePermEnd;

MobyInstance *FindMobyByUID(int unused, int uid)
{
    for (MobyInstance *moby = MobyInstances; moby != MobyInstancePermEnd; moby++) {
        if ((short)moby->uid == uid)
            return moby;
    }

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/respawn", RestoreMobyVarList);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/respawn", RestoreSavedMobyVars);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/respawn", SaveCheckpointMobyVar);
