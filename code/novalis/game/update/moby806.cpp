#include "common.h"
#include "vtbl.h"
#include "moby.h"

int M806_IsActive(MobyInstance *moby)
{
    return moby->state == 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", FUN_00300528);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", func_003005A0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", FUN_003005a8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", FUN_00300808);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", FUN_00300900);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", FUN_00300c40);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", FUN_00300cf8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", FUN_00300d70);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby806", UpdateMoby_806);
