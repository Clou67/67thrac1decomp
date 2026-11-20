#include "common.h"
#include "freeze.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", UpdateMoby_Spaceship);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_SetCutsceneCamera);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawLoadingBanner);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", SetupSpaceShipVars);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DisableShip);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_EnableShip);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", space_PlayCutscene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_StartTakeoffCutscene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", StartLeaveLevelCutscene);

extern int CutscenePlaying;

void ChangeLevel(int level)
{
    g_newlevelnum = level;
    g_newlevel = 1;
    CutscenePlaying = 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", space_StartLevelArrival);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawShipEngineGlow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawShipEffects);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawQuadStrip);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawHelper);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_UpdateCutsceneScene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", TransitionDraw_Space);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_SpawnShipParticles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", UpdateSpace);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", space_DefaultDraw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", SpaceTransition_LoadWad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", DisplayLoadingScreen);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", SpacePlate_DrawQuad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", LoadSpacePlate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", PlaySpacePlate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", DoSpaceTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawTransitionOverlay);
