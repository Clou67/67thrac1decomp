#include "common.h"
#include "vuchain.h"
#include "fastfunc.h"
#include "moby.h"
#include "sce.h"
#include "sound.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", UpdateNumSpawnableMobys);

extern int worldUpdateTime;
extern MobyInstance *MobyInstancePermEnd;
extern MobyInstance *MobyInstanceEnd;
extern unsigned char *mobyVars;
extern int numSpawnableMobys;
extern const char createMobyFailureMessage[] __attribute__((section(".data")));

void InitMobyInstance(MobyInstance *moby, int oClass);

MobyInstance *CreateMoby(int oClass)
{
    for (MobyInstance *moby = MobyInstancePermEnd; moby < MobyInstanceEnd; ++moby) {
        unsigned char state = moby->state;
        if (state < 0xFE)
            continue;

        if (moby->lights > (unsigned int)worldUpdateTime)
            continue;

        if (state == 0xFF)
            moby[1].state = state;

        InitMobyInstance(moby, oClass);

        void *vars = mobyVars + (moby - MobyInstancePermEnd) * 0x80;
        moby->pVar = vars;
        FastMemSet(vars, 0, 0x80);

        if (numSpawnableMobys != 0)
            --numSpawnableMobys;

        return moby;
    }

    printf_stub(createMobyFailureMessage, worldUpdateTime, oClass);
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", InitMobyInstance);


void UpdateMobyGrids(MobyInstance *moby, unsigned int bounds);

void DeleteMoby(MobyInstance *moby)
{
    if (moby < MobyInstancePermEnd)
        moby->state = 0xFD;

    else
        moby->state = 0xFE;

    moby->lights = (unsigned long long)(worldUpdateTime + 2);
    UpdateMobyGrids(moby, 0x80807F7F);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyfunc", UpdateMobyFrameData);

void MB_PlayMobyDesiredSound(MobyInstance* pMoby) {
    int channel;
    SoundAudioState* state;

    if (pMoby->soundChannel != 0xFF) {
        channel = pMoby->soundChannel;
        state = (SoundAudioState*)((SoundVoice*)&audioState + channel);

        if (state->voices[0].pMoby != pMoby)
            pMoby->soundChannel = 0xFF;
            
        else if (state->voices[0].soundId != pMoby->soundDesired) {
            sound_KillChannel(channel);
            pMoby->soundChannel = 0xFF;
        }
        
    } 
    else if (pMoby->soundDesired != 0xFF)
        pMoby->soundChannel = sound_PlayMobySound(pMoby->soundDesired, 4, pMoby);
    
}

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

void AttachManipulator(MobyInstance *moby, int animJoint, Manipulator *manipulator)
{
    if (manipulator->state == 0) {
        manipulator->animJoint = animJoint;
        manipulator->state = 1;

        manipulator->rot.w = 1.0f;
        manipulator->scale.x = 1.0f;
        manipulator->scale.y = 1.0f;
        manipulator->scale.z = 1.0f;

        unsigned char *joint = *(unsigned char **)((unsigned char *)moby->pClass->animationJoints + manipulator->animJoint * 4 + 4);
        manipulator->jointId = joint[*joint + 4] * 0x40 + 0x70000000;

        manipulator->pChain = moby->pManipulators;
        moby->pManipulators = manipulator;
    }
}

void DetachManipulator(MobyInstance *moby, Manipulator *manipulator)
{
    if (manipulator == 0)
        return;

    if (moby->pManipulators == manipulator) {
        moby->pManipulators = manipulator->pChain;
    } else {
        Manipulator *previous = moby->pManipulators;

        for (;;) {
            if (previous->pChain == 0)
                break;
            if (previous->pChain == manipulator)
                break;
            previous = previous->pChain;
        }

        if (previous->pChain == manipulator)
            previous->pChain = manipulator->pChain;
    }

    FastMemSet(manipulator, 0, sizeof(Manipulator));
}

int AnimCache_Register(MobyInstance *moby)
{
    int index = 0;
    MobyInstance **entry = AnimationCacheRegistry;

    for (; index < ANIM_CACHE_COUNT; ++index, ++entry) {
        if (!*entry || *entry == moby) {
            *entry = moby;
            return index;
        }
    }

    return -1;
}

void CleanAnimationCache(void)
{
    for (int slot = 0; slot < ANIM_CACHE_COUNT; ++slot) {
        MobyInstance *moby = AnimationCacheRegistry[slot];
        if (moby != 0 && ((moby->state & 0x80) || moby->updateId != 0xFF))
            AnimationCacheRegistry[slot] = 0;
    }
}

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

void MB_ComputeSelectedJointPos(MobyInstance *moby, int count, int *joints, Vec4 *out);
void FastVec3Add(Vec4 *out, Vec4 *left, Vec4 *right);

void GetMobyJointsWorldPos(MobyInstance *moby, int count, int *joints, Vec4 *out)
{
    float scale = moby->scale * (1.0f / 1024.0f);
    MB_ComputeSelectedJointPos(moby, count, joints, out);

    if (count > 0) {
        do {
            FastVec3Scale(out, out, scale);
            FastVecMtx3Mult(out, out, &moby->transform);
            FastVec3Add(out, out, &moby->pos);
            ++out;
        } while (--count);
    }
}

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
