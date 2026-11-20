#include "common.h"
#include "path.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", InitFollower);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", func_0028B508);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", PathFindClosestPnt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", func_0028B5D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", Path_PickNextNode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", func_0028B780);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", PathFollower_GetPntPtr);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/path", PathFollower_WrapIdx);

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
