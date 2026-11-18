#ifndef MUSIC_H
#define MUSIC_H

void music_Sync(int wait);
// Nonzero while a music_LoadFile read is still streaming in.
extern short CdReadActive[];

void music_LoadFile(void *destination, int sector, int length);
int music_LoadFileSync(void *destination, int sector, int length);

#endif
