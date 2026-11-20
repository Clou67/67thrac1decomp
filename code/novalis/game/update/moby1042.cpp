#include "common.h"
#include "vtbl.h"

int FUN_003040b8(MobyInstance *moby)
{
    return 0;
}

int FUN_003040c0(MobyInstance *moby)
{
    return 0;
}

int FUN_003040c8(MobyInstance *moby, int damageKind, int flags, float amount)
{
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_003040d0);

void DeleteMoby(MobyInstance *moby);

void DeleteMoby_Thunk(MobyInstance *moby)
{
    DeleteMoby(moby);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_003040f8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00304100);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", MB_Sucking);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00304390);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_003044a0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00304690);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00304798);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_003051a8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00305260);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00306158);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00306510);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00306528);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_003067d0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00307850);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_003078b8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", FUN_00307a50);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby1042", UpdateMoby_1042);
