#ifndef MOBYUTIL_H
#define MOBYUTIL_H

int MB_RequestHelpMessage(int selector, int messageId);

void MB_UnlockLevel(int level);
void MB_UnlockItem(int item, char equip);

float Lerp(float from, float to, float weight);

struct MobyInstance;
struct Vec4;

void MB_SetZBoundsFromPos(MobyInstance *moby, float z);

int TweenColor(int from, int to, float fraction);

int DecAlpha(int *rgba, int decrement);

float MB_CollLineWrapper(Vec4 *position);

float MB_catmullRom(float first, float second, float third, float fourth, float fraction);

void *MB_GetPvarsIfMobyHasThem(MobyInstance *moby);

void MB_CopyHeroLights(MobyInstance *moby);

int MB_randInt(int limit);

int MB_randRange(int low, int high);

float MB_randRangeFloat(float low, float high);

float MB_randRangeSigned(float low, float high);

#endif
