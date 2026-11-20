#include "common.h"
#include "vtbl.h"
#include "moby.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby280", FUN_002e0a28);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby280", FUN_002e0a78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby280", FUN_002e0ac8);

int MB_BeginSucking(MobyInstance *moby);
enum { M280_SUCKING = 5 };

void M280_BeginSucking(MobyInstance *moby)
{
    MB_BeginSucking(moby);
    moby->state = M280_SUCKING;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby280", func_002E0BA8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby280", FUN_002e0bd8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby280", UpdateMoby_280);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby280", func_002E0D88);
