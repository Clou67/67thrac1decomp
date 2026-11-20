#include "common.h"
#include "water.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_InitAll);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_CalcGridBsphere);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_LookupTile);

enum { WATER_WAVE_REFERENCE_SAMPLE = 16, WATER_WAVE_SAMPLE_COUNT = 92 };
extern float WaterWaveTable[WATER_WAVE_SAMPLE_COUNT];

void WaterWave_ScaleTable(float height)
{
    float scale = height / WaterWaveTable[WATER_WAVE_REFERENCE_SAMPLE];
    float *sample = WaterWaveTable;

    for (unsigned int index = 0; index < WATER_WAVE_SAMPLE_COUNT; index++)
        *sample++ *= scale;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_StepSim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_UpdateWaves);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/water", WaterTile_UpdateUVs);

void WaterTile_PutDropThunk(WaterTile *tile, int tiles, float x, float y, float radius, float height)
{
    WaterTile_PutDrop(tile, tiles, x, y, radius, height, 0);
}

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
