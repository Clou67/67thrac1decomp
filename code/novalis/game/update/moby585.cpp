#include "common.h"
#include "vtbl.h"
#include "moby.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby585", FUN_002f1c78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby585", FUN_002f1cc8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby585", FUN_002f1d18);

int MB_BeginSucking(MobyInstance *moby);
enum { M585_SUCKING = 7 };

void M585_BeginSucking(MobyInstance *moby)
{
    MB_BeginSucking(moby);
    moby->state = M585_SUCKING;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby585", func_002F1DF8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby585", FUN_002f1e28);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby585", FUN_002f21c0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby585", UpdateMoby_585);
