#ifndef FREEZE_H
#define FREEZE_H

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
