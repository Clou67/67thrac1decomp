#ifndef PAUSE_H
#define PAUSE_H

struct MobyInstance;

enum { GAME_COMPLETE_MOBY_COUNT = 24 };

struct GameCompleteWidget {
    char unk_00[0x44];
    MobyInstance *mobys[GAME_COMPLETE_MOBY_COUNT];
};

struct GoldBoltWidget {
    char unk_00[0x44];
    MobyInstance *moby;
};

struct ImageWidget {
    char unk_00[0x44];
    int image;
    void *streamBuffers[2];
    int unk_50;
    int unk_54;
};

enum { MENU_STREAM_BUFFER_COUNT = 5, MENU_STREAM_LARGE = 1, MENU_STREAM_LOCKED = 4 };

struct MenuStreamBuffer {
    void *data;
    int flags;
};

extern MenuStreamBuffer MenuStreamBuffers[MENU_STREAM_BUFFER_COUNT];

struct MenuClipWidget {
    char unk_00[0x18];
    int x;
    int y;
    int width;
    int height;
};

struct MessageBoxWidget {
    char unk_00[0x54];
    void *streamBuffer;
};

extern int pauseActionListMode;

// State of the pause menu's map page; only the level being shown is known so far.
struct MapPageState {
    char unk0[0x224];
    int level;
};

extern MapPageState MapPage;
extern int pauseActionList[];

int MenuText_OnEnterResetBuffers(void);

void ItemView_SpinMobyUpdate(MobyInstance *moby);

void GoldBolt_SpinMobyUpdate(MobyInstance *moby);

int MapPage_Draw(void);

int GameComplete_Draw(GameCompleteWidget *widget);

int GoldBoltWidget_DeleteMoby(GoldBoltWidget *widget);

int ImageWidget_OnExit(ImageWidget *widget);

int Menu_GetStreamBufferSize(void *data);

int Menu_SetClipRect(MenuClipWidget *widget);

int MessageBox_OnExit(MessageBoxWidget *widget);

#endif
