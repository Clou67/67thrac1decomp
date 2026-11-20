#include "common.h"
#include "vuchain.h"
#include "pause.h"
#include "map.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", map_LoadPlanetMap);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_OnPauseMenuOpen);

int Map_FindFreeCacheSlot(int fromTop)
{
    for (int index = 0; index < MAP_CACHE_SLOT_COUNT; ++index) {
        int slot = fromTop ? MAP_CACHE_SLOT_COUNT - 1 - index : index;
        if (MapPage.cacheBuffers[slot] && MapPage.cacheIds[slot] == -1)
            return slot;
    }
    return -1;
}

enum { MAP_CACHE_KEEP_IN_SLOT = 0x1000 };

int Map_GetFreeCacheSlotCompact(void)
{
    int slot = Map_FindFreeCacheSlot(1);
    if (slot != 0)
        return slot;

    for (slot = 1; slot < MAP_CACHE_SLOT_COUNT; ++slot) {
        if (!(MapPage.cacheIds[slot] & MAP_CACHE_KEEP_IN_SLOT) && MapPage.cacheBuffers[slot])
            break;
    }

    Map_MoveCacheSlot(0, slot);
    return slot;
}

void Map_MoveCacheSlot(int destination, int source)
{
    FastMemCopy16(MapPage.cacheBuffers[destination], MapPage.cacheBuffers[source], MapPage.cacheSizes[source] * 16);
    MapPage.cacheIds[destination] = MapPage.cacheIds[source];
    MapPage.cacheSizes[destination] = MapPage.cacheSizes[source];
    MapPage.cacheIds[source] = -1;
}

int Map_FindCacheSlotById(int id)
{
    for (int slot = 0; slot < MAP_CACHE_SLOT_COUNT; ++slot) {
        if (MapPage.cacheBuffers[slot] && MapPage.cacheIds[slot] == id)
            return slot;
    }
    return -1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_GetNextMapToPrefetch);

enum { GALACTIC_MAP_LEVEL_COUNT = 20 };
extern int *GalacticMapIds;

int Map_GetGalacticMapIndex(int id)
{
    int *entry = GalacticMapIds;
    for (int index = 0; *entry && index < GALACTIC_MAP_LEVEL_COUNT; ++index, ++entry) {
        if (GalacticMapIds[index] == id)
            return index;
    }
    return -1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_ChooseCacheSlotToEvict);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_MergeByMask);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_UpdateZoomPan);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", DrawMapFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DecodeLayer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DecodeLayerRow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", DrawMapFrame_Part2);

int Map_RegionVisible_cc08(int endX, int endY)
{
    return Map_PointSideOfLine(endX, endY, 211, 219, 297, 249);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CC30);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CC40);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CC50);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CC60);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CD20);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CDA0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CE08);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CE18);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CE28);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CE38);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CE48);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025CE58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_ce68);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_d0a8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_d1e0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_d390);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_d450);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D4E0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_d590);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_d648);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D710);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D740);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D798);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D810);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D888);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D8C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D8D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D8E0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D8F0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D900);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D910);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D920);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D960);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D970);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D980);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D990);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D9A0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025D9B0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DA30);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DA90);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DB10);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DBC0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DC58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DC68);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DC98);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DCA0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegionVisible_dca8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DD48);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DD58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DD68);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DD78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025DD88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_FindDecodedLayer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", map_SaveRevealMask);

enum { MAP_IMAGE_RLE = 1 };
void Map_DecompressMapImage_Rle(unsigned char *out, unsigned char *data, int layer);
void Map_DecompressMapImage_Raw(unsigned char *out, unsigned char *data);

void Map_DecompressMapImage(unsigned char *out, unsigned char *data, int layer)
{
    map_stub();
    if (MapPage.available) {
        if (*data & MAP_IMAGE_RLE)
            Map_DecompressMapImage_Rle(out, data, layer);
        else
            Map_DecompressMapImage_Raw(out, data);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DecompressMapImage_Rle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DecompressMapImage_Raw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025E3D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RevealAroundPos);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_GetIconLabel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegisterLevelObject);

enum { MAP_ROTATED_LEVEL_OFFSET = 100, MAP_ROTATED_LEVEL = 6, MAP_TRANSFORM_LAST_LEVEL = 18 };
static const float MAP_COORD_SCALE = 1.0f / 512.0f;
struct MapTransform {
    float offsetU;
    float scaleU;
    float offsetV;
    float scaleV;
};
extern MapTransform MapWorldToMap[];

void Map_WorldToMapCoords(float x, float y, float *outU, float *outV, int level)
{
    int rotated = 0;
    if (level >= MAP_ROTATED_LEVEL_OFFSET) {
        level -= MAP_ROTATED_LEVEL_OFFSET;
        rotated = 1;
    }
    if (level == -1)
        level = Level;
    if (level < 0)
        level = 0;
    if (level > MAP_TRANSFORM_LAST_LEVEL)
        level = 0;

    if (level == MAP_ROTATED_LEVEL && rotated) {
        *outU = (MapWorldToMap[MAP_ROTATED_LEVEL].scaleV * y + 1053.0f) * MAP_COORD_SCALE;
        *outV = (740.0f - MapWorldToMap[MAP_ROTATED_LEVEL].scaleU * x) * MAP_COORD_SCALE;
    }
    else {
        *outU = (MapWorldToMap[level].offsetU + MapWorldToMap[level].scaleU * x) * MAP_COORD_SCALE;
        *outV = (MapWorldToMap[level].offsetV + MapWorldToMap[level].scaleV * y) * MAP_COORD_SCALE;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025E8F8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DrawIcon);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", map_SaveLevelObjectState);

void map_stub(void)
{
}

int Map_PointSideOfLine(int endX, int endY, int startX, int startY, int pointX, int pointY)
{
    int relativeX = pointX - startX;
    int lineX = endX - startX;
    int relativeY = pointY - startY;
    int lineY = endY - startY;
    if ((relativeX * lineY - relativeY * lineX) < 0) return 1;
    return 0;
}
