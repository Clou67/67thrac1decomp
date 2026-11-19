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

void RestoreMobyVarList(MobyVarList *list)
{
    for (int index = 0; index < list->count; index++) {
        MobyVarEntry *entry = &list->entries[index];
        MobyInstance *moby = FindMobyByUID(entry->oClass, entry->uid);
        if (moby != 0) {
            unsigned char *destination;
            if (entry->isMoby == 1)
                destination = (unsigned char *)(entry->offset + (int)moby);
            else
                destination = (unsigned char *)(entry->offset + (int)moby->pVar);
            FastMemCopy32(destination, entry->data, entry->size);
        }
    }
}

extern MobyVarList SavedMobyVars;

void RestoreSavedMobyVars(void)
{
    RestoreMobyVarList(&SavedMobyVars);
}

void SaveCheckpointMobyVar(void *data, int size, MobyInstance *moby, int isMoby, MobyVarList *list)
{
    short uid = moby->uid;
    short oClass = moby->oClass;
    int offset = (short)(isMoby == 1
                       ? (unsigned int)data - (unsigned int)moby
                       : (unsigned int)data - (unsigned short)(unsigned int)moby->pVar);

    for (int index = 0; index < list->count; index++) {
        MobyVarEntry *entry = &list->entries[index];
        if (entry->offset == offset && entry->size == size && uid == entry->uid && oClass == entry->oClass) {
            // A matching entry can change where a newly appended value will be restored.
            isMoby = entry->isMoby;
            if (isMoby != 0) {
                FastMemCopy32(entry->data, data, size);
                return;
            }
        }
    }

    MobyVarEntry *entry = &list->entries[list->count++];
    entry->offset = offset;
    FastMemCopy32(entry->data, data, size);
    entry->size = size;
    entry->isMoby = isMoby;
    entry->uid = uid;
    entry->oClass = oClass;
}
