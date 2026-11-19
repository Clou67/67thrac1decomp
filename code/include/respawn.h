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

#endif
