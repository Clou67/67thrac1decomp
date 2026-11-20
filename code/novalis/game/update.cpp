#include "common.h"
#include "gameglobals.h"
#include "vuchain.h"
#include "music.h"
#include "draw.h"
#include "update.h"

void update_stub(void)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", ResetGameCounters);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", UpdateGameCounters);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", UpdateGameplay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", mode_movieUnInit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", mode_sceneUnInit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", UpdateSceneCamera);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", UpdateInLevelMovie);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", PlayInfobotMovie);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", PlayHelpMovie);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", PlaySpecialMovie);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", StartMovie);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", mode_cinematicInit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", UpdateCinematic);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", mode_creditsInit);

extern int CutscenePlaying;
extern float screenFade;

void mode_creditsUnInit(void)
{
    VU1_syncChain(1);
    FadeToBlack(12);
    music_StopLoad();

    gameMode = 0;
    CutscenePlaying = 1;
    screenFade = 0.0f;
    VU1_setBufSizeByLevel();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update", UpdateCredits);
