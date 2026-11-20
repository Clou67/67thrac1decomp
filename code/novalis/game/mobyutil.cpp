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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_randSphere);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CosineInterpolate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_lerpRotCosine);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetGroupField);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_BallisticTicksToHeight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_BallisticPosAtTicks);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_QuatToEuler);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", Delt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", AccelDelt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDelt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", SubRots);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", DeltAng);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", AccelDeltAng);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDeltAng);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", Float_To_RGBA);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", ReorderRGB_Swap);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", ReorderRGB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_NormalizeMtx3Columns);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetNormalizedMtxElem);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RemoveVecComponent);

struct MobySpecialVars {
    void *pVars;
};

void *MB_GetPvarsIfMobyHasThem(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (moby->modeBits & HAS_SPECIAL_VARS)
        return ((MobySpecialVars *)moby->pVar)->pVars;

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetPVarsField10);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MistDeathEffect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_StartKick);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_UpdateKick);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MtxToQuat);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_TransformToQuat);

void MB_CopyHeroLights(MobyInstance *moby)
{
    moby->lights = Hero.moby->lights;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_AxisAngleToQuat);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", ClampVec3Magnitude);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_AddMobyToDynamicGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DeleteMobyFromDynamicGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_FindMobyByVarId);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00274798);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_randOffset);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_IsPntInCuboid);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_IsPntInCylinder);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_IsPntInSphere);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_QuatMultiply);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RotateQuatAxisAngle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00274B70);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_getTarget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_getTargetInArea);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00275280);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetPlatformParent);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_TransformBetweenFrames);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PlatformLocalToWorld);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PlatformWorldToLocal);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetOrientation);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ScaledVecWrapper);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_BobMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SwingMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00277B48);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SphericalToVector);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_AddVectorSphere);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetUnspentGoldBolts);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CountGoldWeapons);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CountSkillPoints);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CountGoldBolts);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", SetupMobyFunctions);
