#ifndef MUSIC_H
#define MUSIC_H

void music_Sync(int wait);
int music_LoadFileSync(void *destination, int sector, int length);

#endif
