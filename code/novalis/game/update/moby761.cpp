#include "common.h"
#include "vtbl.h"
#include "water.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby761", FUN_002fe080);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby761", FUN_002fe888);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby761", FUN_002fe9f0);

struct WaterSheet;
void WaterSheet_DrawAll(int count, WaterSheet *sheets);
enum { M761_WATER_SHEET_COUNT = 4 };
extern WaterSheet M761_WaterSheets[];

void M761_DrawWaterSheets(MobyInstance *moby)
{
    WaterSheet_Prepare();
    WaterSheet_DrawAll(M761_WATER_SHEET_COUNT, M761_WaterSheets);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby761", UpdateMoby_761);
