#ifndef PATH_H
#define PATH_H

#include "moby.h"

struct SplineNode {
    float x;
    float y;
    float z;
    unsigned int mask;
};

struct MobyPath {
    int pointCount;
    char unk_04[0xC];
    union {
        Vec4 points[1];
        SplineNode nodes[1];
    };
};

struct PathFollower {
    int index;
    signed char pathId;
    unsigned char state;
    unsigned short flags;
    float timer;
    float distance;
    MobyPath *path;
    int splineIdx;
};

int PathFollower_Advance(PathFollower *follower);

int PathFollower_WrapIdx(PathFollower *follower, int index);

int PathFindClosestPnt(float distance, Vec4 *position, MobyPath *path);

void InitFollower(PathFollower *follower);

#endif
