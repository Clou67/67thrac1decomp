#ifndef MOBYUTIL_H
#define MOBYUTIL_H

#include "moby.h"

int MB_RequestHelpMessage(int selector, int messageId);

void MB_UnlockLevel(int level);
void MB_UnlockItem(int item, char equip);

float Lerp(float from, float to, float weight);

struct COLL_DAM_IN {
    Vec4 momentum;
    MobyInstance *pMoby;
    int damageFlags;
    unsigned char damageClass;
    unsigned char damageStrength;
    unsigned short damageIndex;
    float damageHp;
    int flags;
    float damageHeroHp;
    int shotUID;
    int pad;
};
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

float MB_randRot(void);

void MB_randVector(Vec4 *vector, float low, float high);

void SetCollDamIn(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp);

void SetCollDamIn_2(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp, Vec4 *momentum);

#endif
