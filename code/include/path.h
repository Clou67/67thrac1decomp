#ifndef PATH_H
#define PATH_H

#include "moby.h"

struct SplineNode {
    float x;
    float y;
    float z;
    unsigned int mask;
};

struct MobySpline {
    int pointCount;
    char unk_04[12];
    SplineNode nodes[1];
};

struct MobyPath {
    int pointCount;
    char unk_04[0xC];
    Vec4 points[1];
};

struct PathFollower {
    int index;
    signed char pathId;
    char unk_05[0xB];
    MobyPath *path;
};

int PathFollower_Advance(PathFollower *follower);

int PathFollower_WrapIdx(PathFollower *follower, int index);

#endif
