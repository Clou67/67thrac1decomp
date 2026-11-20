#include "common.h"
#include "moby.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", FUN_003027e8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", FUN_00302840);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", FUN_003028c8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", FUN_00302a50);

int M849_CallClassCallback04(MobyInstance *moby)
{
    MobyClassCallback callback = moby->pClass->callbacks->callback04;

    int result;
    if (!callback)
        result = 1;

    else
        result = callback(moby);

    return result;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", FUN_00302ac0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", FUN_00302bd0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", FUN_00302ed0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", func_00302FFC);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", UpdateMoby_849);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby849", func_003040B4);
