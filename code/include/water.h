#ifndef WATER_H
#define WATER_H

struct WaterTile;

void WaterTile_PutDrop(WaterTile *tile, int tiles, float x, float y, float radius, float height, int mode);

void WaterSheet_Prepare(void);

void WaterTile_PutDropThunk(WaterTile *tile, int tiles, float x, float y, float radius, float height);

#endif
