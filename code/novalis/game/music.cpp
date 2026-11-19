#include "common.h"
#include "music.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Init);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_RegisterBankCB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Helpgirl);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Qwark);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Space);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Help);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Bindata);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Vendor);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_PlayPreseekedSpeech);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_PreseekTrack);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartTrack);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartTrackBody);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Transition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_SetTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Stop);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Pause);

enum { MUSIC_COMMAND_RESUME = 4 };

void music_Unpause(void)
{
    musicTransition.primary_command = MUSIC_COMMAND_RESUME;
    musicTransition.transition_command = MUSIC_COMMAND_RESUME;
    musicTransition.secondary_command = MUSIC_COMMAND_RESUME;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_UnpauseDelay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_UpdateStream);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StopLoad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_LoadBankFromEE);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_LoadFile);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_LoadFileSync);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Sync);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_LoadBankCB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AD88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_SpeechPreseekCB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_PreseekTrackCB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AE78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AEC8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AF20);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StopCB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AFB8);
