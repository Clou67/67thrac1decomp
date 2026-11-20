#ifndef MOBYUTIL_H
#define MOBYUTIL_H

enum { MOBY_GROUP_INDEX_MASK = 0x7FFF };

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

enum { GOLD_BOLT_LEVEL_COUNT = 20, GOLD_BOLT_SLOTS_PER_LEVEL = 4 };
extern unsigned char GoldBoltFlags[GOLD_BOLT_LEVEL_COUNT][GOLD_BOLT_SLOTS_PER_LEVEL];

enum { GOLD_WEAPON_FLAG_COUNT = 37 };
extern unsigned char GoldWeaponFlags[GOLD_WEAPON_FLAG_COUNT];

enum { SKILL_POINT_FLAG_COUNT = 32 };
extern unsigned char SkillPointFlags[SKILL_POINT_FLAG_COUNT];

int MB_CountGoldBolts(void);

int MB_CountGoldWeapons(void);

int MB_CountSkillPoints(void);

int MB_GetUnspentGoldBolts(void);

void MB_SetGroupField(int group, int value);

float MB_CosineInterpolate(float start, float end, float weight);

float MB_lerpRotCosine(float start, float end, float weight);

float MB_BallisticTicksToHeight(Vec4 *start, Vec4 *velocity, float gravity, int *ticksOut);

void MB_BallisticPosAtTicks(Vec4 *out, Vec4 *start, Vec4 *velocity, float gravity, int ticks);

void MB_RemoveVecComponent(Vec4 *out, Vec4 *vector, Vec4 *axis, float weight);

void MB_BobMotion(MobyInstance *moby, float *phase, float *offset, float height, float phaseStep);

void MB_SphericalToVector(Vec4 *out, float radius, float azimuth, float elevation);

void MB_randSphere(Vec4 *out, float minimum, float maximum);

void MB_randOffset(Vec4 *vector, float range);

void MB_QuatMultiply(Vec4 *out, Vec4 *vector, Vec4 *rotation);

void MB_QuatToEuler(Vec4 *out, Vec4 *angles);

void MB_RotateQuatAxisAngle(Vec4 *out, Vec4 *vector, Vec4 *axis, float angle);

unsigned int Float_To_RGBA(float red, float green, float blue, float alpha);

unsigned int ReorderRGB(unsigned int rgba, int mask);

void MB_SetStateByGroup(int group, int value);

int MB_PushMobyOutOfWalls(MobyInstance *moby, Vec4 *move, float height, float stepHeight, int radiusFixed, int flags);

void MB_RotateMoby(MobyInstance *moby, float xAngle, float yAngle, float zAngle);

float MB_computeLobVelocity(Vec4 *from, Vec4 *to, float speed, float gravity, float *timeOut);

int MB_IsInvalidOrClass502(MobyInstance *moby);

int MB_HasCollPrims(MobyInstance *moby);

#endif
