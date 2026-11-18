#include "common.h"
#include "freeze.h"
#include "draw.h"
#include "fastfunc.h"
#include "font.h"
#include "gameglobals.h"
#include "gsregs.h"
#include "help.h"
#include "hud.h"
#include "memcard.h"
#include "music.h"
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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/freeze", UpdateModeFreeze);

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
