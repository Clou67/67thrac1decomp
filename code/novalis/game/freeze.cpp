#include "common.h"
#include "freeze.h"
#include "mcstate.h"
#include "draw.h"
#include "fastfunc.h"
#include "font.h"
#include "gameglobals.h"
#include "hero.h"
#include "gsregs.h"
#include "help.h"
#include "hud.h"
#include "memcard.h"
#include "music.h"
#include "pad.h"
#include "pause.h"
#include "sound.h"
#include "vuchain.h"

#define SAVE_DIALOG_MAX_SIZE 0x20000

// Frames the prompt waits before it can be dismissed.
#define PROMPT_DEFAULT_TIMER 0x78
#define PROMPT_TIMER_FRAMES 30

// Sound group that is paused while the game is frozen.
#define FREEZE_SOUND_GROUP 0x1D

// Message ids of the texts the prompts show.
#define MSG_PROMPT_0_TITLE 0x4F6E
#define MSG_PROMPT_0_YES 0x5248
#define MSG_PROMPT_0_NO 0x5249
#define MSG_PROMPT_OK 0x524A
#define MSG_PROMPT_1_TITLE 0x5229
#define MSG_PROMPT_1_BODY 0x4EE0

// Message that is logged as seen when the save-failed prompt appears.
#define HELP_MSG_SAVE_FAILED 0x4E2B

// Frames of the delayed-continue freeze before the prompt fades and before it can be left.
#define FREEZE_DELAYED_FADE_FRAMES 0x5A
#define FREEZE_DELAYED_CONTINUE_FRAMES 0x78

#define LEVEL_NOVALIS 1
#define LEVEL_RILGAR 5
#define LEVEL_KALEBO_3 0x10

#define FREEZE_DISPATCH_FADE_FRAMES 30
#define FREEZE_RETRY_TIME_FRAMES 0x1068
#define VIDEO_TEST_TIMEOUT_FRAMES 0x258
#define CONFIRM_BOX_STEPS 8

enum video_test_state {
    VIDEO_TEST_INPUT_DELAY,
    VIDEO_TEST_AWAIT_START,
    VIDEO_TEST_PREVIEW_ACTIVE,
    VIDEO_TEST_AWAIT_TIMEOUT_ACK
};

enum confirm_state {
    CONFIRM_PREPARE,
    CONFIRM_AWAIT_INPUT,
    CONFIRM_ACCEPT,
    CONFIRM_CANCEL
};

// Level select map.
#define LEVEL_MARKER_COUNT 20
#define MAP_WIDTH 0x200
#define MAP_HEIGHT_NTSC 0x1A0
#define MAP_HEIGHT_PAL 0x1C0
#define MAP_TEXTURE 0xE99A
#define MAP_FRAME_MARKER 0xC
#define MAP_FRAME_SELECTION 0xD
#define MAP_FRAME_BACKGROUND 0xE
#define MAP_FRAME_CLOUDS 0xF
#define MAP_CLOUD_SCROLL_MASK 0xFFF
#define MAP_ALPHA_OPAQUE 0x80
#define MAP_ALPHA_BLEND 0x8000000044UL
#define MAP_ATEST 0x4B
#define MAP_BLACK 0x80000000
#define MAP_LABEL_COLOR 0x80F0F0F0
#define MAP_BLINK_ON_FRAMES 0x16
#define MAP_BLINK_OFF_FRAMES 8
#define MAP_LINE_GAP 8000

enum map_level_state {
    MAP_LEVEL_LOCKED,
    MAP_LEVEL_UNLOCKED = 2,
    MAP_LEVEL_VISITED
};

int MediumFontHeight = 17;

int GetLastFreezeDialogType(void)
{
    return Freeze.prevGameMode;
}

void mode_freezeInit(int dialog, int restorePage)
{
    if (gameMode != GAME_MODE_PAUSE) {
        snd_PauseAllSoundsInGroup(FREEZE_SOUND_GROUP);
        music_Pause(0);
    }

    Freeze.prevGameMode = gameMode;
    Freeze.restorePage = restorePage;
    gameMode = GAME_MODE_FREEZE;
    Freeze.mode = dialog;

    switch (dialog) {
    case FREEZE_DIALOG_CONFIRM:
        Freeze.query = msg_string(MSG_PROMPT_0_TITLE);
        Freeze.ans1 = msg_string(MSG_PROMPT_0_YES);
        Freeze.ans2 = msg_string(MSG_PROMPT_0_NO);
        Freeze.countdown = 0;
        Freeze.updTimers[0] = 0;
        Freeze.updTimers[1] = 0;
        Freeze.updTimers[2] = 0;
        Freeze.updTimers[3] = 0;
        break;
    case 2:
        Freeze.query = msg_string(MSG_PROMPT_OK);
        Freeze.ans1 = 0;
        Freeze.countdown = 0;
        break;
    case 1:
    case 4:
        Freeze.query = msg_string(MSG_PROMPT_1_TITLE);
        Freeze.ans1 = msg_string(MSG_PROMPT_1_BODY);
        Freeze.ans2 = msg_string(MSG_PROMPT_OK);
        Freeze.countdown = 0;
        break;
    case FREEZE_DIALOG_LOG_HELP:
        Help_AddToLog(HELP_MSG_SAVE_FAILED);
        Freeze.countdown = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        Freeze.updTimers[1] = 0;
        Freeze.updTimers[2] = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        break;
    case FREEZE_DIALOG_SAVE_FAILED:
        Freeze.countdown = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        Freeze.updTimers[1] = 0;
        Freeze.updTimers[2] = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        break;
    case 6:
        Freeze.countdown = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        Freeze.updTimers[0] = 0;
        break;
    default:
        Freeze.query = 0;
        Freeze.ans1 = 0;
        Freeze.ans2 = 0;
        Freeze.countdown = PROMPT_DEFAULT_TIMER;
        break;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/freeze", DrawDialogText);

// Data DrawDialogText reads (layout rectangles and its jump tables) until the function is matched.
__asm__(
 ".section .rodata\n"
 ".align 4\n"
 ".word 0x01540050, 0x01A00060, 0x00540100, 0x00000000\n"
 ".word 0x00010010, 0x00000000, 0x012C0064, 0x01A00060\n"
 ".word 0x00680100, 0x00000000, 0x00010010, 0x00000000\n"
 ".word 0x00224150, 0x00224868, 0x002247B0, 0x00223B6C\n"
 ".word 0x00224868, 0x00223848, 0x00223F5C, 0x00000000\n"
 ".word 0x00223C0C, 0x00223CBC, 0x00223CBC, 0x00223D08\n"
 ".word 0x00223BB0, 0x00223BE4, 0x00223BE4, 0x00223D4C\n"
 ".word 0x00223BDC, 0x00223BDC, 0x00223BBC, 0x00223BD0\n"
 ".word 0x00223BEC, 0x00223BEC, 0x00223D4C, 0x00223BF4\n"
 ".word 0x00223C00, 0x00223C2C, 0x00223C84, 0x00223C78\n"
 ".word 0x00223D4C, 0x00223CB4, 0x00223C90, 0x00000000\n"
 ".section .text\n"
);

void UpdateModeFreeze(void)
{
    int step;
    int video_mode;
    freeze_t *frozen;

    sound_Update();

    if (Freeze.countdown != 0) {
        Freeze.countdown--;
    }

    switch (Freeze.mode) {
    case FREEZE_MODE_DELAYED_CONTINUE:
        frozen = &Freeze;
        frozen->updTimers[1]++;
        if (FastScaleRoundInt(FREEZE_DELAYED_FADE_FRAMES) < frozen->updTimers[1]) {
            if (frozen->updTimers[2] != 0) {
                frozen->updTimers[2]--;
            }
        }

        frozen = &Freeze;
        if (FastScaleRoundInt(FREEZE_DELAYED_CONTINUE_FRAMES) < frozen->updTimers[1]) {
            if (padState.bitsOn & PAD_CROSS) {
                gameMode = GAME_MODE_NORMAL;
                if (Level == LEVEL_NOVALIS) {
                    memcard_Save(0, -1);
                }
            }
        }
        break;
    case FREEZE_MODE_TRIANGLE_HIDE_HERO:
        if (padState.bitsOn & PAD_TRIANGLE) {
            MobyInstance *moby = Hero.moby;

            moby->enabled = 0;
            moby->collision = 0;
            moby->modeBits |= DISABLED;
            Hero_RevertToRatchet();
            Hero_Warp(&Hero.savedPosRot[0], &Hero.savedPosRot[4], 0, 1);
            gameMode = GAME_MODE_NORMAL;
        } else if (padState.bitsOn & PAD_CROSS) {
            gameMode = GAME_MODE_NORMAL;
        }
        break;
    case FREEZE_MODE_VIDEO_MODE_TEST:
        switch (Freeze.updTimers[0]) {
        case VIDEO_TEST_INPUT_DELAY:
            if (Freeze.countdown != 0) {
                Freeze.countdown--;
                if (Freeze.countdown == 0) {
                    Freeze.updTimers[0] = VIDEO_TEST_AWAIT_START;
                }
            } else {
                Freeze.updTimers[0] = VIDEO_TEST_AWAIT_START;
            }
            break;
        case VIDEO_TEST_AWAIT_START:
            if (padState.bitsOn & PAD_TRIANGLE) {
                gameMode = Freeze.prevGameMode;
            } else if (padState.bitsOn & PAD_CROSS) {
                FadeToBlack(4);
                PalModeRequest = 0;
                Freeze.updTimers[0] = VIDEO_TEST_PREVIEW_ACTIVE;
                Freeze.updTimers[1] = FastScaleRoundInt(VIDEO_TEST_TIMEOUT_FRAMES);
            }
            break;
        case VIDEO_TEST_PREVIEW_ACTIVE:
            if (Freeze.updTimers[1] == 0 || --Freeze.updTimers[1] == 0) {
                PalModeRequest = 1;
                Freeze.updTimers[0] = VIDEO_TEST_AWAIT_TIMEOUT_ACK;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                FadeToBlack(4);
                PalModeRequest = 1;
                gameMode = Freeze.prevGameMode;
            } else if (padState.bitsOn & PAD_CROSS) {
                PalModeRequest = 0;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case VIDEO_TEST_AWAIT_TIMEOUT_ACK:
            if (padState.bitsOn & PAD_CROSS) {
                gameMode = Freeze.prevGameMode;
            }
            break;
        default:
            gameMode = Freeze.prevGameMode;
            break;
        }
        break;
    case FREEZE_MODE_TRIANGLE_SET_SHIP_FLAG:
        OcclMode = 2;
        if (padState.bitsOn & PAD_TRIANGLE) {
            gameMode = GAME_MODE_NORMAL;
            Hero.shipFlags |= HERO_SHIP_FLAG_RESET;
        } else if (padState.bitsOn & PAD_CROSS) {
            gameMode = GAME_MODE_NORMAL;
        }
        break;
    case FREEZE_MODE_AWAIT_CROSS:
        OcclMode = 2;
        if (padState.bitsOn & PAD_CROSS) {
            gameMode = GAME_MODE_NORMAL;
        }
        break;
    case FREEZE_MODE_CONFIRM_CANCEL:
        switch (Freeze.updTimers[0]) {
        case CONFIRM_PREPARE:
            if (Freeze.updTimers[1] < CONFIRM_BOX_STEPS) {
                Freeze.updTimers[1]++;
            } else if (Freeze.updTimers[2] < CONFIRM_BOX_STEPS) {
                Freeze.updTimers[2]++;
            } else {
                Freeze.updTimers[0] = CONFIRM_AWAIT_INPUT;
            }
            break;
        case CONFIRM_AWAIT_INPUT:
            if (padState.bitsOn & PAD_CROSS) {
                Freeze.updTimers[0] = CONFIRM_ACCEPT;
            } else if (padState.bitsOn & (PAD_CIRCLE | PAD_START)) {
                Freeze.updTimers[0] = CONFIRM_CANCEL;
            }

            video_mode = PalModeRequest; // fakematch
            if (video_mode >= 0) { // fakematch
                break; // fakematch
            } // fakematch
        case CONFIRM_ACCEPT:
        case CONFIRM_CANCEL:
            if (Freeze.updTimers[2] != 0) {
                Freeze.updTimers[2]--;
            } else if (Freeze.updTimers[1] != 0) {
                Freeze.updTimers[1]--;
            } else {
                step = Freeze.updTimers[0];
                video_mode = PalModeRequest; // fakematch
                if (video_mode < 0) { // fakematch
                    Freeze.updTimers[0] = step; // fakematch
                } else if (step == CONFIRM_ACCEPT) {
                    if (Hero.trickHudHandle != HERO_NO_HUD_HANDLE) {
                        Hud_SetEntryValueById(Hero.trickHudHandle, 0);
                        Hero.trickHudHandle = HERO_NO_HUD_HANDLE;
                    }
                    HudStub();
                    if (FastScaleRoundInt(FREEZE_RETRY_TIME_FRAMES) < Hero.controlModeTimer) {
                        if (Level == LEVEL_RILGAR) {
                            RilgarRetryCount++;
                        } else if (Level == LEVEL_KALEBO_3) {
                            KaleboRetryCount++;
                        }
                    }
                    gameMode = GAME_MODE_NORMAL;
                    Hero_Warp(&Hero.savedPosRot[0], &Hero.savedPosRot[4], 0, 1);
                } else {
                    gameMode = GAME_MODE_NORMAL;
                    if (Hero.raceLap >= HERO_RACE_LAP_COUNT) {
                        Hero.raceLap--;
                        Hero.raceMoby[HERO_RACE_MOBY_LAP_OFFSET] = HERO_RACE_LAP_COUNT;
                    }
                }
            }
            break;
        }
        break;
    case FREEZE_MODE_STATE_DISPATCH:
        Freeze.updTimers[1]++;
        if (FastScaleRoundInt(FREEZE_DISPATCH_FADE_FRAMES) < Freeze.updTimers[1]) {
            if (Freeze.updTimers[2] != 0) {
                Freeze.updTimers[2]--;
            }
        }

        switch (mc_state) {
        case CS_GOOD_LOAD:
            if (Freeze.countdown == 0) {
                if (padState.bitsOn & PAD_CROSS) {
                    mcstate_flags &= ~MCSTATE_FLAG_CARD_CHANGED;
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        case CS_PROMPT_FORMAT:
            if (padState.bitsOn & PAD_CIRCLE) {
                mcstate_flags |= MCSTATE_FLAG_FORMAT_YES;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                if (InFrontEnd == 0) {
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        case CS_PROMPT_CREATE_SAVE:
            if (padState.bitsOn & PAD_CIRCLE) {
                mcstate_flags |= MCSTATE_FLAG_CREATE_YES;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                if (InFrontEnd == 0) {
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        case CS_PROMPT_FORMAT_FAILED:
        case CS_PROMPT_CREATE_FAILED:
        case CS_PROMPT_LOAD_FAILED:
        case CS_PROMPT_SAVE_FAILED:
            if (padState.bitsOn & PAD_CROSS) {
                mcstate_flags ^= MCSTATE_FLAG_PROMPT;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_NEWCARD:
            gameMode = Freeze.prevGameMode;
            pauseActionList[0] = Freeze.restorePage;
            break;
        case CS_NOSAVE:
            if (mcstate_flags & MCSTATE_FLAG_SAVE) {
                break;
            }
        case CS_NOCARD:
        case CS_UNFORMATTED:
            if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_NO_ROOM:
            if (InFrontEnd != 0 && (mcstate_flags & MCSTATE_FLAG_SAVE)) {
                if (padState.bitsOn & PAD_CROSS) {
                    memcard_ResetGame();
                    mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                    mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                    mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                    ChangeLevel(0);
                    LevelChangePending[0] = 1;
                } else if (padState.bitsOn & PAD_TRIANGLE) {
                    mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                    mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                    gameMode = Freeze.prevGameMode;
                }
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_PROMPT_BEGIN_UNFORMATTED:
        case CS_PROMPT_BEGIN_NOSAVE:
            if (padState.bitsOn & PAD_CROSS) {
                memcard_ResetGame();
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                ChangeLevel(0);
                LevelChangePending[0] = 1;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_WAIT_FOR_CARD:
            if (InFrontEnd != 0) {
                if (mcstate_flags & MCSTATE_FLAG_SAVE) {
                    if (padState.bitsOn & PAD_CROSS) {
                        memcard_ResetGame();
                        mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                        mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                        ChangeLevel(0);
                        LevelChangePending[0] = 1;
                    }

                    if (padState.bitsOn & PAD_TRIANGLE) {
                        mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                        mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                        mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                        gameMode = Freeze.prevGameMode;
                    }
                } else if (mcstate_flags & MCSTATE_FLAG_LOAD) {
                    if (padState.bitsOn & PAD_TRIANGLE) {
                        mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                        mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                        mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                        gameMode = Freeze.prevGameMode;
                    }
                } else {
                    gameMode = Freeze.prevGameMode;
                }
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_FORMATTED:
            if (InFrontEnd != 0) {
                if (!(mcstate_flags & (MCSTATE_FLAG_SAVE | MCSTATE_FLAG_LOAD))) {
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        }
        break;
    }

    if ((unsigned int)(gameMode - GAME_MODE_PAUSE) >= 2) {
        snd_ContinueAllSoundsInGroup(FREEZE_SOUND_GROUP);
        music_Unpause();
        snd_FlushSoundCommands();
    }
}

int GetSaveDialogRect(unsigned int size, void **first, void **second)
{
    if (size > SAVE_DIALOG_MAX_SIZE) {
        *first = 0;
        *second = 0;
        return -1;
    }

    *first = MemSlots.vu1_chain[0] + vu1_bufSize - size;
    *second = MemSlots.vu1_chain[1] + vu1_bufSize - size;

    return 0;
}

void DrawMessageBox(int left, int right, int top, int bottom)
{
    float labelDirection[4];
    int level;
    int frame;
    int availability;
    int width;
    int height;
    int markerX;
    int markerY;
    int labelX;
    int labelY;
    int lineStartX;
    int lineStartY;
    int directionLength;
    int lineFraction;
    int textWidth;
    int lineEndX;
    int textX;
    char *label;

    FlipAndExploreTimersVU1(0);
    VU1_addGSregister(GS_REG_ALPHA_1, MAP_ALPHA_BLEND);
    VU1_addGSregister(GS_REG_TEST_1, MAP_ATEST);
    Hud_DrawFlatRectFixed(0, 0, MAP_WIDTH, MAP_HEIGHT_PAL, MAP_BLACK, 0);

    frame = HudTex_GetFrame(MAP_TEXTURE, MAP_FRAME_BACKGROUND);
    width = (right - left) * 16;
    height = (bottom - top) * 16;
    Hud_DrawTexQuadF(frame, 0, 0, width, height, 0, 0, MAP_ALPHA_OPAQUE);
    VU1_addGSregister(GS_REG_CLAMP_1, GS_CLAMP_REPEAT);
    Hud_DrawTexQuadF(HudTex_GetFrame(MAP_TEXTURE, MAP_FRAME_CLOUDS), 0, 0, width, height, gsFrame & MAP_CLOUD_SCROLL_MASK, 0, MAP_ALPHA_OPAQUE);
    VU1_addGSregister(GS_REG_CLAMP_1, GS_CLAMP_CLAMP);

    for (level = 1; level < LEVEL_MARKER_COUNT; level++) {
        if (LevelMapMarkers[level].x == 0) {
            continue;
        }

        if (LevelVisited[level] != 0) {
            availability = MAP_LEVEL_VISITED;
        } else if (LevelUnlocked[level] == 0) {
            availability = MAP_LEVEL_LOCKED;
        } else {
            availability = MAP_LEVEL_UNLOCKED;
        }

        if (availability == MAP_LEVEL_LOCKED) {
            continue;
        }

        markerX = LevelMapMarkers[level].x;
        markerY = LevelMapMarkers[level].y;
        if (videoModePal != 0) {
            markerY = markerY * MAP_HEIGHT_PAL / MAP_HEIGHT_NTSC;
        }

        if (availability == MAP_LEVEL_VISITED || (availability == MAP_LEVEL_UNLOCKED && gsFrame % (FastScaleRoundInt(MAP_BLINK_ON_FRAMES) + FastScaleRoundInt(MAP_BLINK_OFF_FRAMES)) < FastScaleRoundInt(MAP_BLINK_ON_FRAMES))) {
            Hud_DrawTexQuad(HudTex_GetFrame(MAP_TEXTURE, MAP_FRAME_MARKER), markerX - 5, markerY - 5, 10, 10, MAP_ALPHA_OPAQUE);
        }

        if (level == MapPage.level) {
            labelX = markerX + LevelMapMarkers[level].labelOffsetX;
            labelY = markerY + LevelMapMarkers[level].labelOffsetY;
            labelDirection[1] = LevelMapMarkers[level].labelOffsetY;
            labelDirection[0] = LevelMapMarkers[level].labelOffsetX;
            directionLength = FastVec3Length(labelDirection) * 1000.0f;
            lineFraction = directionLength - MAP_LINE_GAP;
            lineStartX = labelX + (markerX - labelX) * lineFraction / directionLength;
            lineStartY = labelY + (markerY - labelY) * lineFraction / directionLength;

            label = msg_string(LevelSelectTexts[level].labelText);
            textWidth = FontLen(label, -1);
            if (LevelMapMarkers[level].labelOffsetX <= -1) {
                lineEndX = labelX - textWidth;
            } else {
                lineEndX = labelX + textWidth;
            }

            Hud_DrawFlatRect(lineStartX + 1, lineStartY + 1, labelX + 1, labelY + 1, MAP_BLACK, 0);
            Hud_DrawFlatRect(labelX + 1, labelY + 1, lineEndX + 1, labelY + 1, MAP_BLACK, 0);
            textX = (lineEndX < labelX) ? lineEndX : labelX;
            FontPrintMediumLeft(textX + 1, labelY - MediumFontHeight + 1, MAP_BLACK, label, -1);

            Hud_DrawFlatRect(lineStartX, lineStartY, labelX, labelY, MAP_LABEL_COLOR, 0);
            Hud_DrawFlatRect(labelX, labelY, lineEndX, labelY, MAP_LABEL_COLOR, 0);
            FontPrintMediumLeft(textX, labelY - MediumFontHeight, MAP_LABEL_COLOR, label, -1);

            Hud_DrawTexQuad(HudTex_GetFrame(MAP_TEXTURE, MAP_FRAME_SELECTION), markerX - 10, markerY - 10, 20, 20, MAP_ALPHA_OPAQUE);
        }
    }

    FinalizeVU1FramePacketChain();
}
