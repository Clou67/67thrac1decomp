#ifndef MAP_H
#define MAP_H

// Bytes of map reveal mask kept for each level.
#define MAP_REVEAL_MASK_SIZE 0x800

extern char MapRevealMasks[];

void map_SaveLevelObjectState(void);
void map_SaveRevealMask(char *mask);

int Map_PointSideOfLine(int endX, int endY, int startX, int startY, int pointX, int pointY);

int Map_RegionVisible_cc08(int endX, int endY);

void map_stub(void);

int Map_FindCacheSlotById(int id);

void Map_MoveCacheSlot(int destination, int source);

#endif
