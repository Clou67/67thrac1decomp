#ifndef MOBYUTIL_H
#define MOBYUTIL_H

int MB_RequestHelpMessage(int selector, int messageId);

void MB_UnlockLevel(int level);
void MB_UnlockItem(int item, char equip);

float Lerp(float from, float to, float weight);

#endif
