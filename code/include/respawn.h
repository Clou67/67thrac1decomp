#ifndef RESPAWN_H
#define RESPAWN_H

struct MobyVarEntry {
    int offset;
    unsigned char data[4];
    unsigned short size;
    short isMoby;
    short uid;
    short oClass;
};

struct MobyVarList {
    int count;
    MobyVarEntry entries[64];
};

void ClearCheckpointData(void);

struct MobyInstance;
MobyInstance *FindMobyByUID(int unused, int uid);

void RestoreMobyVarList(MobyVarList *vars);
void RestoreSavedMobyVars(void);

void SaveCheckpointMobyVar(void *data, int size, MobyInstance *moby, int isMoby, MobyVarList *list);

struct BoltSourceStats {
    short uid;
    short bolts;
};
extern BoltSourceStats BoltSources[][64];

int NAVG_AllocSlot(int level, int uid);

#endif
