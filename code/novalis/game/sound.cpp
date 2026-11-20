#include <stddef.h>

#include "common.h"
#include "sound.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_CamOfs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_Occl);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_GetFade);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_GetFadeChannel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_GetPan);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_Init);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_IsHandlePlaying);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", func_002A1338);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_KillChannel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_Play);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_PlayMobySound);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_MobyPlayByClass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_LevelPlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", func_002A1800);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_AmbientPlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_FootstepPlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", func_002A1960);

int sound_SetVol(int handle, int volume)
{
    unsigned int offset = handle * sizeof(SoundVoice);
    unsigned char *voice = (unsigned char *)(offset + (unsigned int)&audioState);
    *(int *)(voice + offsetof(SoundAudioState, voices[0].volume)) = volume;
    return 1;
}

int sound_SetPitch(int handle, int pitch)
{
    unsigned int offset = handle * sizeof(SoundVoice);
    unsigned char *voice = (unsigned char *)(offset + (unsigned int)&audioState);
    *(int *)(voice + offsetof(SoundAudioState, voices[0].pitch_bend)) = pitch;
    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_SetupAmbientFunctions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_UpdateAmbient);

enum { REVERB_TYPE = 1, REVERB_DELAY_FEEDBACK = 2, REVERB_DEPTH = 4 };

void sound_SetReverb(int owner, int type, int depth, int delay, int feedback)
{
    audioState.reverb_owner = owner;
    if (audioState.reverb_type != type) {
        audioState.reverb_type = type;
        audioState.reverb_commands |= REVERB_TYPE;
    }

    if (audioState.reverb_depth != depth) {
        audioState.reverb_depth = depth;
        audioState.reverb_commands |= REVERB_DEPTH;
    }

    if (audioState.reverb_delay != delay || audioState.reverb_feedback != feedback) {
        audioState.reverb_feedback = feedback;
        audioState.reverb_delay = delay;
        audioState.reverb_commands |= REVERB_DELAY_FEEDBACK;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", sound_StopAllSounds);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", func_002A1BB0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", func_002A1BC8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/sound", func_002A1C10);
