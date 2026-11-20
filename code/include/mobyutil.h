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
struct Mtx4;

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

void ReorderRGB_Swap(int *red, int *green, int *blue, int mask);

int MB_GetPVarsField10(MobyInstance *moby);

void MB_TransformToQuat(Vec4 *quaternion, Mtx4 *transform);

float Delt(float &value, float target, float step);

void MB_AxisAngleToQuat(Vec4 *quaternion, Vec4 *axis, float angle);

void MB_AddVectorSphere(Vec4 *out, Vec4 *origin, float radius, float azimuth, float elevation);

MobyInstance *MB_GetPlatformParent(MobyInstance *moby);

void ClampVec3Magnitude(Vec4 *vector, float maximum);

int MB_ScaledVecWrapper(Vec4 *vector, float radius);

int MB_CountGoldBolts(void);

int MB_CountGoldWeapons(void);

int MB_CountSkillPoints(void);

int MB_GetUnspentGoldBolts(void);

void MB_SetGroupField(int group, int value);

float MB_CosineInterpolate(float start, float end, float weight);

#endif
