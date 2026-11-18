#ifndef FREEZE_H
#define FREEZE_H

// Values of freeze_t::mode.
enum freeze_mode {
    FREEZE_MODE_CONFIRM_CANCEL,
    FREEZE_MODE_TRIANGLE_SET_SHIP_FLAG,
    FREEZE_MODE_AWAIT_CROSS,
    FREEZE_MODE_STATE_DISPATCH,
    FREEZE_MODE_TRIANGLE_HIDE_HERO,
    FREEZE_MODE_DELAYED_CONTINUE,
    FREEZE_MODE_VIDEO_MODE_TEST
};

// Dialog ids for mode_freezeInit.
#define FREEZE_DIALOG_CONFIRM 0
#define FREEZE_DIALOG_SAVE_FAILED 3
#define FREEZE_DIALOG_LOG_HELP 5

// State of the dialog shown while the game is frozen.
struct freeze_t {
    int mode;
    int countdown;
    char *query;
    char *ans1;
    char *ans2;
    int prevGameMode;
    int restorePage;
    int updTimers[4];
};

extern freeze_t Freeze;

// Which occlusion the frozen scene is drawn with.
extern int OcclMode;

// Nonzero while the video mode test wants PAL.
extern unsigned char PalModeRequest;

extern short LevelChangePending[];
extern int RilgarRetryCount;
extern int KaleboRetryCount;

void ChangeLevel(int level);

int GetLastFreezeDialogType(void);
void mode_freezeInit(int dialog, int restorePage);

// Places the two buffers the save dialog reads a save into; fails if the save is too big.
int GetSaveDialogRect(unsigned int size, void **first, void **second);

// Level select map. DrawMessageBox draws the map overlay of the level select screen.
struct LevelMapMarker {
    int x;
    int y;
    int labelOffsetX;
    int labelOffsetY;
};

struct LevelSelectText {
    int descriptionText;
    int labelText;
    int unk8;
};

extern LevelSelectText LevelSelectTexts[];
extern LevelMapMarker LevelMapMarkers[];
extern unsigned char LevelUnlocked[];
extern int MediumFontHeight;

void DrawMessageBox(int left, int right, int top, int bottom);

#endif
