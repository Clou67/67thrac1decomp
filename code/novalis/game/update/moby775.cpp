#include "common.h"
#include "vtbl.h"
#include "moby.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby775", FUN_002ff768);

void DeleteMoby(MobyInstance *moby);

void UpdateMoby_775(MobyInstance *moby)
{
    moby->alpha -= 3;
    moby->scale *= 1.025f;

    if ((unsigned char)moby->alpha < 4)
        DeleteMoby(moby);
}
