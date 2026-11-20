#include "common.h"
#include "vtbl.h"
#include "water.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby676", FUN_002f5040);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby676", FUN_002f5168);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby676", func_002F60F4);

struct WaterSheet;
void WaterSheet_DrawAll(int count, WaterSheet *sheets);
extern WaterSheet WaterSheets[];
enum { WATER_SHEET_COUNT = 8 };

void M676_DrawWaterSheets(MobyInstance *moby)
{
    WaterSheet_Prepare();
    WaterSheet_DrawAll(WATER_SHEET_COUNT, WaterSheets);
}

void RegisterMobyDraw(void (*draw)(MobyInstance *), MobyInstance *moby);
void M676_DrawWaterSheets(MobyInstance *moby);

void UpdateMoby_676(MobyInstance *moby)
{
    RegisterMobyDraw(M676_DrawWaterSheets, moby);
}
