#ifndef FREEZE_H
#define FREEZE_H

// Prompt ids for DisplayPrompt.
#define PROMPT_PAUSE 0
#define PROMPT_SAVE_FAILED 3
#define PROMPT_PUSH_HELP_HISTORY 5

// State of the prompt shown while the game is frozen.
struct FreezePrompt {
    int prompt;
    int timer;
    char *text[3];
    int previousGameMode;
    int arg;
    int choice;
    int boxTimer;
    int fadeStep;
    int unk28;
};

extern FreezePrompt Freeze;

int GetFreezePrevGameMode(void);
void DisplayPrompt(int prompt, int arg);

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
