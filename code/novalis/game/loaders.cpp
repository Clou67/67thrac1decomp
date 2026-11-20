#include "common.h"
#include "vuchain.h"
#include "moby.h"
#include "loaders.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadByteGrid);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", RelocEffectTable);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseGsRamTextures);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", func_00253640);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseParticleTexs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseEffectTexs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseSky);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseMobyPack);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadHudBanks);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadCompressedHudBank);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", SetUpVisGif);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", SetUpVisGifViewer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParsePermGsRam);

void ParseMobySeq(MobyClass *mobyClass, int animation)
{
    MobySeq *sequence = mobyClass->animations[animation];
    char *base = (char *)sequence;

    if (sequence->triggers)
        sequence->triggers = (short *)(base + (int)sequence->triggers);

    if (sequence->frameCount) {
        int index = 0;
        MobySeqFrame **frame = sequence->frames;
        do {
            *frame = (MobySeqFrame *)(base + (int)*frame);
            ++frame;
        } while (++index < sequence->frameCount);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseMobyClass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseTieClass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseShrubClass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseTfrag);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseColl);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", PrintMobyMemory);

void STUB_RET_255950(void *data, int count)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ResetLevelData);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", SetupLevelWadBuffer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadLevelFiles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", InitLevelFromWad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", PreLoadNpcChunk);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseNpcChunk);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadWeaponCutscene);

struct SceneLoadState {
    char unk_00[0x58];
    unsigned char *decodedChunk;
    unsigned char *buffer;
    unsigned char *chunks[1];
};

extern SceneLoadState SceneLoad;
void ParseNpcChunk(void);

void ParseWeaponSceneChunk(int chunk)
{
    SceneLoad.buffer = SceneLoad.chunks[chunk];
    ParseNpcChunk();
    SceneLoad.buffer = MemSlots.vu1_chain[1] + vu1_bufSize;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadSpaceScene);

void ParseSpaceSceneChunk(int chunk)
{
    SceneLoad.buffer = SceneLoad.chunks[chunk];
    ParseNpcChunk();
    SceneLoad.buffer = MemSlots.vu1_chain[1] + vu1_bufSize;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadMobyModel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", QueuePifLoad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", QueuePifLoad_Raw);
