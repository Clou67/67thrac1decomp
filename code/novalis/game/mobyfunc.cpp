#include "common.h"
#include "vuchain.h"
#include "fastfunc.h"
#include "moby.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", UpdateNumSpawnableMobys);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", CreateMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", InitMobyInstance);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DeleteMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", UpdateMobyFrameData);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_PlayMobyDesiredSound);

enum { ANIM_TICKS_PER_FRAME = 16 };

int MB_FindNearestAnimTrigger(MobySeq *sequence, float time)
{
    short key = FastFloatToInt(time * ANIM_TICKS_PER_FRAME);
    for (int index = 0; index < sequence->frameCount; ++index) {
        int frameTime = sequence->frames[index]->time;
        if (frameTime > key) {
            if (index > 0 && key - sequence->frames[index - 1]->time < frameTime - key)
                --index;
            return index;
        }
    }
    return -1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", func_00263918);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_BlendAnimFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", func_00263A18);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_GetCollPrimWorld);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_SetCollPrimFromWorld);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_AddShortPairOffset);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_AllocAnimLayer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_FreeAnimLayer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_UpdateAnimLayer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_StartAnimLayer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_InitAnimLayerBuffer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", AttachManipulator);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DetachManipulator);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", AnimCache_Register);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", CleanAnimationCache);

void MobyComputeSelectedJoints(MobyInstance *moby, int count, int *indices, Mtx4 *joints);
void FastMtx3x4Copy(Mtx4 *out, Mtx4 *source);
void FastMtxTransform(Mtx4 *out, Mtx4 *left, Mtx4 *right);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_GetBoneTransformation(MobyInstance *moby, int index, Mtx4 *out)
{
    Mtx4 world;
    float scale = moby->scale * (1.0f / 1024.0f);

    MobyComputeSelectedJoints(moby, 1, &index, out);
    FastVec3Scale(&out->v3, &out->v3, scale);
    FastMtx3x4Copy(&world, &moby->transform);
    FastMtxTransform(out, &world, out);
    FastVec3Add(&out->v3, &out->v3, &moby->pos);
}

void MobyComputeSelectedJoints(MobyInstance *moby, int count, int *indices, Mtx4 *joints);
void FastVecMtx3Mult(Vec4 *out, Vec4 *vector, Mtx4 *matrix);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_GetBonePos(MobyInstance *moby, int index, Vec4 *out)
{
    Mtx4 joint;
    float scale = moby->scale * (1.0f / 1024.0f);

    MobyComputeSelectedJoints(moby, 1, &index, &joint);
    FastVec3Scale(out, &joint.v3, scale);
    FastVecMtx3Mult(out, out, &moby->transform);
    FastVec3Add(out, out, &moby->pos);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", GetMobyJointsWorldPos);

void MB_GetJointsWorldMtx(MobyInstance *moby, int count, int *indices, Mtx4 *joints)
{
    Mtx4 world;
    float scale = moby->scale * (1.0f / 1024.0f);

    FastMtx3x4Copy(&world, &moby->transform);
    MobyComputeSelectedJoints(moby, count, indices, joints);
    for (int index = 0; index < count; ++index) {
        Mtx4 *joint = &joints[index];
        FastMtxTransform(joint, &world, joint);
        FastVec3Scale(&joint->v3, &joint->v3, scale);
        FastVec3Add(&joint->v3, &joint->v3, &moby->pos);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DmaMobyTextures);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", PatchMobyGifs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_UpdateLightAngle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DrawMobyShadows);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", ProcessMobyAnimData);

enum { DEFAULT_MOBY_CLASS_DISTANCE = 0x40000000, MOBY_CLASS_DISTS_SIZE = 0x380 };

static int *const MobyClassDists = (int *)0x70003A00;

void InitMobyClassDists(void)
{
    FastMemSet(MobyClassDists, DEFAULT_MOBY_CLASS_DISTANCE, MOBY_CLASS_DISTS_SIZE);
}

void StashMobyClassDists(void)
{
    FastMemCopy16(StashedMobyClassDists, MobyClassDists, MOBY_CLASS_DISTS_SIZE);
}

void RestoreMobyClassDists(void)
{
    FastMemCopy16(MobyClassDists, StashedMobyClassDists, MOBY_CLASS_DISTS_SIZE);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DrawMobysSetup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DrawMobyListProc);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DrawMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", DrawMobys);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_SetLightsFromEnvSample);

extern int Level;
extern unsigned char occlCharTable[][16];

void SetLevelFlag(int flag)
{
    if (flag != 0xFF)
        occlCharTable[Level][flag] = 0xFF;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", SetColorOfMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", SetColorOfMoby_Part);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", GetColorOfMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_GetLightDirection);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_GetLightColor);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MB_BSphereGap);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", UpdateMobyAnimFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", FindMobysCloseToUpdate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MobyGrid_Free);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", MobyGrid_Alloc);
