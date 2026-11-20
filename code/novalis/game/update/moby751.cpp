#include "common.h"
#include "vtbl.h"
#include "water.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby751", FUN_002fcd88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby751", FUN_002fce68);

enum { M751_WATER_TILE_COUNT = 21 };
extern WaterTile M751_WaterTiles[];
void WaterTile_DrawAll(WaterTile *tiles, int count);

void M751_DrawWaterTiles(MobyInstance *moby)
{
    WaterTile_DrawAll(M751_WaterTiles, M751_WATER_TILE_COUNT);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby751", UpdateMoby_751);
