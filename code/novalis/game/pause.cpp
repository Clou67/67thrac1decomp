#include "common.h"
#include "gsregs.h"
#include "vuchain.h"
#include "fastfunc.h"
#include "moby.h"
#include "pause.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", LoadHudSeqs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ResetMenuCamera);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", BeginMenu);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", FrontEnd_UpdateMenu);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", FrontEnd_InitMenu);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", UpdatePause);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", FrontEnd_DrawMenu);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_0028D768);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", HudTableHandleExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", IconList_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", IconList_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_0028DBB8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", BuildCheatsList);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_0028DD10);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_0028DD18);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_0028DD20);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawHudTables);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", UpdatePauseMenu);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawPauseStrings);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", GetMenuFadeColor);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_0028F1B0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuButton_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_0028F7A0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MapPage_OnExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MapPage_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Missions_OnEnter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Missions_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SlotConfig_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_002903D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00290468);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_002904A0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_002904D0);

void Menu_InitStreamBuffers(int reset);

int MenuText_OnEnterResetBuffers(void)
{
    Menu_InitStreamBuffers(1);
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00290508);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SoundOptions_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawSoundOptionsFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00290B70);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00290BF8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MusicWidget_OnEnter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MusicWidget_OnExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MusicWidget_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawSkillPointsFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuButton_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_002917D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00291930);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00291938);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ItemView_OnExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ItemView_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ItemView_Draw);

void ItemView_SpinMobyUpdate(MobyInstance *moby)
{
    moby->rotation.z = FastAddRots(moby->rotation.z, 0.01f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", WeaponView_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", WeaponView_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", WeaponView_MobyUpdate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_002921D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", PlanetInfo_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", GoldBoltWidget_SpawnMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", GoldBoltWidget_DeleteMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", GoldBoltWidget_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Update_FoundGBsShipMenu);

void GoldBolt_SpinMobyUpdate(MobyInstance *moby)
{
    moby->rotation.x = FastAddRots(moby->rotation.x, 0.02f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ItemInfo_DrawCost);

void DrawMapFrame(void);
enum { MAP_ALPHA_BLEND = 0x44, MAP_DRAW_RESULT = 8 };

int MapPage_Draw(void)
{
    VU1_addGSregister(GS_REG_ALPHA_1, MAP_ALPHA_BLEND);
    VU1_addGSregister(GS_REG_TEST_1, GS_TEST_ATE | GS_TEST_ATST_GEQUAL);

    DrawMapFrame();
    return MAP_DRAW_RESULT;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MapMenu_DrawOptions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ExitSelectPrompt_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawMissionsFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawFlatOverlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ImageWidget_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ImageWidget_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ImageWidget_OnEnter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ImageWidget_OnExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", UpdateOptionsMenus);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ImageWidget_DrawWithText);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", HelpControls_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", HelpControls_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MapPage_DrawOverlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SlotConfig_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ConfirmDialog_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ConfirmDialog_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", CameraSettings_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawCameraSettingsFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00295000);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", GoldWeapons_OnEnter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00295200);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00295208);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00295310);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_SetClipRect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", PlanetSelect_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MessageBox_OnEnter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MessageBox_OnExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_002954C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MessageBox_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00295730);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuCycle30_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuCycle12_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuIconText_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", LevelFilter_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", ShowScreenAfterDrekDefeat);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00295DE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SecretMenu_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SecretMenu_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawUnusedCompletedGameFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Draw_GameCompletedFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SaveSlotInfo_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SaveLoad_OnEnter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SaveLoad_OnExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SaveGame_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SaveLoad_Update2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", LoadGame_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawSaveLoadFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", DrawTVTextures);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SpawnHeroInMenu);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", UpdateAfterEquipGadget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00298568);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00298570);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_MobyUpdateA);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_MobyUpdateB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_MobyUpdateC);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_MobyUpdateD);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_MobyUpdateE);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_MobyUpdateF);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_CreateMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_DeleteMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_UnlockLevelWidget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_00299188);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Spawn_Moby1957_HelpdeskLady);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", GameComplete_OnExit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", M1957_Update_GirlwadOnGameComplete);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", GameComplete_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", func_002996C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_InitStreamBuffers);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_AllocStreamBuffer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_FreeStreamBuffer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_GetStreamBufferSize);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_LockStreamBuffer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_UnlockStreamBuffer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", LoadMenuRatchetModel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_FreeResources);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_LoadAnimSet);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_StopStreamLoad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_InitSpriteRect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", MenuHero_SetupMobyList);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Menu_StashImage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SaveGame_SaveMapState);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", SaveGame_Write);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", PrepareChallengeModeSave);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", Respawn_IncCounter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pause", BeginMenu_InitHudTables);
