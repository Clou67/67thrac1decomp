#include "common.h"
#include "fastfunc.h"
#include "path.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", InitFollower);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", func_0028B508);

float FastAbsF(float value);

int PathFindClosestPnt(float distance, Vec4 *position, MobyPath *path)
{
    int closest = 0;
    float bestDistance = 100000000000.0f;
    for (int index = 0; index < path->pointCount; ++index) {
        float pointDistance = FastVec3Dist(&path->points[index], position);
        if (FastAbsF(pointDistance - distance) < bestDistance) {
            bestDistance = pointDistance;
            closest = index;
        }
    }
    return closest;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", func_0028B5D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", Path_PickNextNode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", func_0028B780);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", PathFollower_GetPntPtr);

int PathFollower_WrapIdx(PathFollower *follower, int index)
{
    int last = follower->pathId >= 0 ? follower->path->pointCount - 1 : 0;

    if (index < 0)
        return last + index;
    if (index > last)
        return index % (last + 1);
    return index;
}

int PathFollower_Advance(PathFollower *follower)
{
    int last = 0;
    if (follower->pathId >= 0)
        last = follower->path->pointCount - 1;

    int index = follower->index + 1;
    if (index > last)
        index %= last + 1;
    follower->index = index;
    return index;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", Spline_CalcTan);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", Spline_Hermite);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", Spline_CalcLen);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", func_0028BE30);
