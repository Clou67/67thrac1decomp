#ifndef FREEZE_H
#define FREEZE_H

extern char FontNormalMetrics[];
extern int freezeStatsTimeRefA[2];
extern int freezeStatsScoreRefA[2];

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

// Text and format strings of the freeze dialogs.
extern char FreezeEmptyText[];
extern char FreezeFormatPrompt[];
extern char FreezeFormatIndented[];
extern char FreezeFormatFirst[];
extern char FreezeFormatSecond[];
extern char FreezeFormatThird[];
extern char FreezeFormatNth[];
extern char FreezeFormatString[];
extern char FreezeFormatTime[];
extern char FreezeFormatNumber[];

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

#endif
