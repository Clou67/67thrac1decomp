#include "common.h"
#include "water.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_InitAll);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_CalcGridBsphere);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_LookupTile);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterWave_ScaleTable);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_StepSim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_UpdateWaves);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_UpdateUVs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_PutDropThunk);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_PutDrop);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_GetHeight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_BuildVertexGrid);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_CullAndDrawCell);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_DrawCellOvl);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_DrawAll);

void SetupVU1WorldDraw(void);

void WaterSheet_Prepare(void)
{
    SetupVU1WorldDraw();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterSheet_DrawAll);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", func_002B9A30);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", UpdateWater);
