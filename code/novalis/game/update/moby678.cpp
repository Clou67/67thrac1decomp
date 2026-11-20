#include "common.h"
#include "vtbl.h"
#include "water.h"

struct WaterSheet;
void WaterSheet_DrawAll(int count, WaterSheet *sheets);
enum { M678_WATER_SHEET_COUNT = 2 };
extern WaterSheet M678_WaterSheets[];

void M678_DrawWaterSheets(MobyInstance *moby)
{
    WaterSheet_Prepare();
    WaterSheet_DrawAll(M678_WATER_SHEET_COUNT, M678_WaterSheets);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/moby678", UpdateMoby_678);
