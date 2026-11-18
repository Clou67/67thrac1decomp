#ifndef MAP_H
#define MAP_H

// Bytes of map reveal mask kept for each level.
#define MAP_REVEAL_MASK_SIZE 0x800

extern char MapRevealMasks[];

void map_SaveLevelObjectState(void);
void map_SaveRevealMask(char *mask);

#endif
