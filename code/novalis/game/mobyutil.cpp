#include "common.h"
#include "mathfunc_inline.h"
#include "fastfunc.h"
#include "moby.h"
#include "hero.h"
#include "mobyutil.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DropAmmo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnBoltsFromCrate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetAnimationNoBlend);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetAnimation);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetAnimationFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026C900);

int RandomNext(void);

int MB_randInt(int limit)
{
    return ((RandomNext() >> 16) & 0x7FFF) % limit;
}

int MB_randRange(int low, int high)
{
    return ((RandomNext() >> 16) & 0x7FFF) % (high - low + 1) + low;
}

float MB_randRangeFloat(float low, float high)
{
    int sample = (RandomNext() >> 16) & 0x7FFF;
    float range = high - low;

    return low + (float)sample * range * (1.0f / 32768.0f);
}

float MB_randRangeSigned(float low, float high)
{
    int sample = RandomNext() >> 16;
    float range = high - low;
    float value = low + (float)(sample & 0xFFF) * range * (1.0f / 4096.0f);

    if (sample & 1)
        value = -value;

    return value;
}

float MB_randRot(void)
{
    int sample = (RandomNext() >> 16) & 0xFFF;

    return (float)(sample - 2048) * 3.14159265358979323846f * (1.0f / 2048.0f);
}

float MB_randRot(void);
float MB_randRangeFloat(float low, float high);
void MB_SphericalToVector(Vec4 *out, float radius, float azimuth, float elevation);

void MB_randVector(Vec4 *vector, float low, float high)
{
    float azimuth = MB_randRot();
    float elevation = MB_randRot();
    float radius = MB_randRangeFloat(low, high);

    MB_SphericalToVector(vector, radius, azimuth, elevation);
}

void MB_randSphere(Vec4 *out, float minimum, float maximum)
{
    float radius = MB_randRangeFloat(minimum, maximum);
    float azimuth = MB_randRot();
    float elevation = MB_randRot();

    out->x = FastAngleSinF(azimuth) * FastAngleCosF(elevation) * radius;
    out->y = FastAngleCosF(azimuth) * FastAngleCosF(elevation) * radius;
    out->z = FastAngleSinF(elevation) * radius;
}

float MB_catmullRom(float first, float second, float third, float fourth, float fraction)
{
    float firstDelta = first - second;
    float cubic = (fourth - third) - firstDelta;
    float fractionSquared = fraction * fraction;
    float linear = third - first;
    float fractionCubed = fractionSquared * fraction;
    float quadratic = firstDelta - cubic;

    return cubic * fractionCubed + quadratic * fractionSquared + linear * fraction + second;
}

float MB_CosineInterpolate(float start, float end, float weight)
{
    if (weight == 0.0f)
        return start;
    if (weight == 1.0f)
        return end;

    float blend = (1.0f - FastAngleSinF(weight * 3.14159265358979323846f)) * 0.5f;
    return start + (end - start) * blend;
}

float FastSubRots(float first, float second);

float MB_lerpRotCosine(float start, float end, float weight)
{
    float delta = FastSubRots(end, start);
    float blend = (1.0f - FastAngleSinF(weight * 3.14159265358979323846f)) * 0.5f;

    return FastAddRots(start, delta * blend);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CosineInterpolateUnitVec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CosineInterpolateAngVec);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DeltAngSpeed);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDeltAngSpeed);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026D1C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", GetGroundZ);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollMovingSphere);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026D608);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PushOutOfWalls);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PushMobyOutOfWalls);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_InitDefaultParams);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MoveAndCollide);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026DE78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MoveAndCollide2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026DFF8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CountActiveMobysByGroup);

extern short *MobyGroupEntries[];
extern MobyInstance *MobyInstances;
enum { MOBY_GROUP_INDEX_MASK = 0x7FFF };

void MB_SetGroupField(int group, int value)
{
    if (MobyGroupEntries[group]) {
        short *entry = MobyGroupEntries[group];
        do {
            int mobyIndex = *entry & MOBY_GROUP_INDEX_MASK;
            MobyInstances[mobyIndex].setByGroup = value;
        } while (*entry++ >= 0);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetStateByGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetFirstMobyInGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetNextMobyInGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026E3A0);

int DecAlpha(int *rgba, int decrement)
{
    int color = *rgba;
    int alpha = (color >> 24) - decrement;

    if (alpha < 0)
        alpha = 0;

    *rgba = (color & 0x00FFFFFF) | (alpha << 24);
    return alpha == 0;
}

float MB_BallisticTicksToHeight(Vec4 *start, Vec4 *velocity, float gravity, int *ticksOut)
{
    int ticks = FastFloatToInt(velocity->z / gravity);
    float duration = FastIntToFloat(ticks);
    float gravityDuration = FastIntToFloat((ticks * ticks + ticks) >> 1);
    float height = start->z + velocity->z * duration - gravityDuration * gravity;

    if (ticksOut)
        *ticksOut = ticks;

    return height;
}

void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_BallisticPosAtTicks(Vec4 *out, Vec4 *start, Vec4 *velocity, float gravity, int ticks)
{
    Vec4 displacement;

    FastVec3Scale(&displacement, velocity, FastIntToFloat(ticks));
    displacement.z -= FastIntToFloat((ticks * ticks + ticks) >> 1) * gravity;
    FastVec3Add(out, start, &displacement);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SolveQuad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CollLineDown);

float MB_CollLineDown(Vec4 *position, float distance, int flags);

enum { COLLISION_PROBE_FLAGS = 0x20 };

float MB_CollLineWrapper(Vec4 *position)
{
    return MB_CollLineDown(position, 0.5f, COLLISION_PROBE_FLAGS);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026E6B8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", PointInsideComplexPoly);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026E790);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_HasCollPrims);

void FastVecZero(Vec4 *vector);

void SetCollDamIn(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp)
{
    damage.pMoby = damager;
    damage.damageFlags = damageFlags;
    damage.damageHp = damageHp;
    damage.flags = 0;

    FastVecZero(&damage.momentum);
}

enum { COLL_DAMAGE_HAS_MOMENTUM = 1 };

void SetCollDamIn_2(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp, Vec4 *momentum)
{
    damage.pMoby = damager;
    damage.damageFlags = damageFlags;
    damage.damageHp = damageHp;
    damage.flags = COLL_DAMAGE_HAS_MOMENTUM;

    CopyVec4Inline(&damage.momentum, momentum);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", DamageSphereAtPos);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollDamageMobyDirect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollDamageMobyDirect_2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026EBE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CollLineMulti);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollWaterHeight);

void FastQuatToEuler(Vec4 *out, float angle, int axis);
void FastQuaternionMult(Vec4 *out, Vec4 *left, Vec4 *right);

void MB_QuatToEuler(Vec4 *out, Vec4 *angles)
{
    Vec4 zRotation, yRotation, xRotation;

    FastQuatToEuler(&xRotation, angles->x, 0);
    FastQuatToEuler(&yRotation, angles->y, 1);
    FastQuatToEuler(&zRotation, angles->z, 2);
    FastQuaternionMult(out, &xRotation, &yRotation);
    FastQuaternionMult(out, out, &zRotation);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RegisterLameShadow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026EFF0);

void MB_SetZBoundsFromPos(MobyInstance *moby, float z)
{
    const float padding = 0.2f;
    moby->zMin = z - padding;
    moby->zMax = z + padding;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetZBoundsFromGround);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetZBoundsFromFloorCeil);

int TweenColor(int from, int to, float fraction)
{
    return FastTweenColor(from, to, fraction);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_FindSlotByMask);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_HandleDamage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026F868);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DamageMobyList);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ReadDamagePush);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_computeLobVelocity);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_randPrimPoints);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00270330);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_updateJump);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_002705A0);

float Lerp(float from, float to, float weight)
{
    return from + (to - from) * weight;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", Lerp_vec4);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00270650);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", GainDampLimit);

float FastAbsF(float value);

float Delt(float &value, float target, float step)
{
    float delta = target - value;

    if (delta > step)
        delta = step;
    else if (delta < -step)
        delta = -step;

    value += delta;
    return FastAbsF(target - value);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", AccelDelt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDelt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", SubRots);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", DeltAng);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", AccelDeltAng);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDeltAng);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", Float_To_RGBA);

enum { SWAP_RED_GREEN = 1, SWAP_GREEN_BLUE = 2, SWAP_BLUE_RED = 4 };

void ReorderRGB_Swap(int *red, int *green, int *blue, int mask)
{
    if (mask & SWAP_RED_GREEN) {
        int saved = *red;
        *red = *green;
        *green = saved;
    }

    if (mask & SWAP_GREEN_BLUE) {
        int saved = *green;
        *green = *blue;
        *blue = saved;
    }

    if (mask & SWAP_BLUE_RED) {
        int saved = *blue;
        *blue = *red;
        *red = saved;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", ReorderRGB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_NormalizeMtx3Columns);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetNormalizedMtxElem);

void FastVec3Normalize(Vec4 *out, Vec4 *vector, float magnitude);
float FastVec3Dot(Vec4 *first, Vec4 *second);
void FastSubVec3(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_RemoveVecComponent(Vec4 *out, Vec4 *vector, Vec4 *axis, float weight)
{
    Vec4 component;
    Vec4 unitAxis;

    FastVec3Normalize(&unitAxis, axis, 1.0f);
    float scale = FastVec3Dot(&unitAxis, vector) * weight;
    FastVec3Scale(&component, &unitAxis, scale);
    FastSubVec3(out, vector, &component);
}

struct MobySpecialVars {
    void *pVars;
    char unk_04[4];
    MobyInstance *platformParent;
    char unk_0C[4];
    int unk_10;
};

void *MB_GetPvarsIfMobyHasThem(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (moby->modeBits & HAS_SPECIAL_VARS)
        return ((MobySpecialVars *)moby->pVar)->pVars;

    return 0;
}

int MB_GetPVarsField10(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (moby->modeBits & HAS_SPECIAL_VARS)
        return ((MobySpecialVars *)moby->pVar)->unk_10;

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MistDeathEffect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_StartKick);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_UpdateKick);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MtxToQuat);

void FastMtx3x4Copy(Mtx4 *destination, Mtx4 *source);
void FastMtx4Copy(Mtx4 *destination, Mtx4 *source);
void MB_MtxToQuat(Vec4 *quaternion, Mtx4 *matrix);

void MB_TransformToQuat(Vec4 *quaternion, Mtx4 *transform)
{
    Mtx4 matrix;

    FastMtx3x4Copy(&matrix, transform);
    MB_MtxToQuat(quaternion, &matrix);
    FastMtx4Copy(transform, &matrix);
}

void MB_CopyHeroLights(MobyInstance *moby)
{
    moby->lights = Hero.moby->lights;
}

void MB_AxisAngleToQuat(Vec4 *quaternion, Vec4 *axis, float angle)
{
    float halfAngle = angle * 0.5f;

    FastVec3Scale(quaternion, axis, FastAngleCosF(halfAngle));
    quaternion->w = FastAngleSinF(halfAngle);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ClampVecToPlanes);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetOrientationMtx);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_UpdateLightsTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ColorDyingMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathStepIndex);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathMoveDist);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0027292C);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DistIgnoreSmallZ);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SegmentPushDist2D);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SegmentPush);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathFollowToPos);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_002731C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_WrapRot);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_IsInvalidOrClass502);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_isCrate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_isAmmo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_genericExplosion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnExplosionSparks);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnExplosionSparks2);

float FastVec3Length2(Vec4 *vector);
void FastVec3Normalize(Vec4 *out, Vec4 *vector, float magnitude);

void ClampVec3Magnitude(Vec4 *vector, float maximum)
{
    if (FastVec3Length2(vector) > maximum)
        FastVec3Normalize(vector, vector, maximum);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_AddMobyToDynamicGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DeleteMobyFromDynamicGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_FindMobyByVarId);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00274798);

void MB_randOffset(Vec4 *vector, float range)
{
    vector->x += MB_randRangeFloat(-range, range);
    vector->y += MB_randRangeFloat(-range, range);
    vector->z += MB_randRangeFloat(-range, range);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_IsPntInCuboid);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_IsPntInCylinder);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_IsPntInSphere);

void FastQuaternionMult(Vec4 *out, Vec4 *left, Vec4 *right);

void MB_QuatMultiply(Vec4 *out, Vec4 *vector, Vec4 *rotation)
{
    Vec4 inverse, point, rotated;

    FastVec3Scale(&inverse, rotation, -1.0f);
    inverse.w = rotation->w;
    CopyVec4Inline(&point, vector);
    point.w = 0.0f;

    FastQuaternionMult(&rotated, rotation, &point);
    FastQuaternionMult(out, &rotated, &inverse);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RotateQuatAxisAngle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00274B70);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_getTarget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_getTargetInArea);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00275280);

MobyInstance *MB_GetPlatformParent(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (!(moby->modeBits & HAS_SPECIAL_VARS))
        return 0;

    return ((MobySpecialVars *)moby->pVar)->platformParent;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_TransformBetweenFrames);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PlatformLocalToWorld);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PlatformWorldToLocal);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetOrientation);

int FastBsphereCheck(Vec4 *sphere, float radius);

int MB_ScaledVecWrapper(Vec4 *vector, float radius)
{
    Vec4 scaled;

    FastScaleVec4(&scaled, vector, 1.0f / 1024.0f);
    return FastBsphereCheck(&scaled, radius);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_UnlockLevel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_UnlockItem);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DistributeBolts);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0027624C);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", SetNtscPalTiming);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00276378);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_compressVector);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_decompressVector);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RoundToDecimals);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MayaFrameTrigger);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_LineCrossesSpline);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SplineIntersect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SplineCrossCheck);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SplineSegmentsReachable);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00276CB0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CollideSplineWall);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SplineFindRouteNode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathPosAtDist);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RotateMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CreateMotionBlur);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", AddMotionBlurElem);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", UpdateMotionBlur);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", DeleteMotionBlur);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_002777C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_TurnHeadJoint);

void MB_BobMotion(MobyInstance *moby, float *phase, float *offset, float height, float phaseStep)
{
    *phase = FastAddRots(*phase, phaseStep);
    moby->pos.z -= *offset;
    *offset = FastAngleCosF(*phase) * height;
    moby->pos.z += *offset;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SwingMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00277B48);

void MB_SphericalToVector(Vec4 *out, float radius, float azimuth, float elevation)
{
    out->x = FastAngleSinF(azimuth) * radius * FastAngleSinF(elevation);
    out->y = FastAngleCosF(azimuth) * radius * FastAngleSinF(elevation);
    out->z = FastAngleCosF(elevation) * radius;
}

void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_AddVectorSphere(Vec4 *out, Vec4 *origin, float radius, float azimuth, float elevation)
{
    Vec4 offset;

    MB_SphericalToVector(&offset, radius, azimuth, elevation);
    FastVec3Add(out, &offset, origin);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ToastMessageByIndex);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathEvalSpline);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_HeroStandingOnMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00278010);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SampleByteGrid);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnGridParticles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DrawGlowFX);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_002783A0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetPointAheadOfMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnBonePartFx);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ToggleManipulator);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00278790);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DistributeBoltsNearHero);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnSparksPair);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ToastMessage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ToastMessageFmt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00278AD0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnDebrisMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnReplacementMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_HandleGameplayHud);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ShowPersistentMessage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RequestHelpMessage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ClearHelpMessage);

int MB_CountGoldWeapons(void);
int MB_CountSkillPoints(void);

int MB_GetUnspentGoldBolts(void)
{
    int goldWeapons = MB_CountGoldWeapons();
    int balance = goldWeapons - MB_CountSkillPoints() * 4;

    if (balance < 0)
        balance = 0;
    if (balance > 40)
        balance = 40;
    return balance;
}

enum { GOLD_WEAPON_LEVEL_COUNT = 20, GOLD_WEAPON_SLOTS = 4 };
extern unsigned char GoldWeaponFlags[GOLD_WEAPON_LEVEL_COUNT][GOLD_WEAPON_SLOTS];

int MB_CountGoldWeapons(void)
{
    int count = 0;

    for (int level = 0; level < GOLD_WEAPON_LEVEL_COUNT; ++level) {
        unsigned char *flag = GoldWeaponFlags[level];
        for (int slot = GOLD_WEAPON_SLOTS - 1; slot >= 0; --slot) {
            if (*flag++)
                ++count;
        }
    }

    if (count < 0)
        count = 0;
    if (count > 40)
        count = 40;
    return count;
}

extern unsigned char SkillPointFlags[37];

int MB_CountSkillPoints(void)
{
    int count = 0;

    for (int index = 0; index < 37; ++index) {
        if (SkillPointFlags[index])
            ++count;
    }

    if (count < 0)
        count = 0;
    if (count > 10)
        count = 10;
    return count;
}

extern unsigned char GoldBoltFlags[32];

int MB_CountGoldBolts(void)
{
    int count = 0;

    for (int index = 0; index < 32; ++index) {
        if (GoldBoltFlags[index])
            ++count;
    }

    if (count < 0)
        count = 0;
    if (count > 30)
        count = 30;
    return count;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", SetupMobyFunctions);
