#include "common.h"
#include "map.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", map_LoadPlanetMap);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_OnPauseMenuOpen);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_FindFreeCacheSlot);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_GetFreeCacheSlotCompact);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_MoveCacheSlot);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_FindCacheSlotById);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_GetNextMapToPrefetch);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_GetGalacticMapIndex);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DecompressMapImage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DecompressMapImage_Rle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DecompressMapImage_Raw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025E3D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RevealAroundPos);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_GetIconLabel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_RegisterLevelObject);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_WorldToMapCoords);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", func_0025E8F8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", Map_DrawIcon);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", map_SaveLevelObjectState);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/map", map_stub);

int Map_PointSideOfLine(int endX, int endY, int startX, int startY, int pointX, int pointY)
{
    int relativeX = pointX - startX;
    int lineX = endX - startX;
    int relativeY = pointY - startY;
    int lineY = endY - startY;
    if ((relativeX * lineY - relativeY * lineX) < 0) return 1;
    return 0;
}
