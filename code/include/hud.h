#ifndef HUD_H
#define HUD_H

struct HudEntry {
    char unk00[0x48];
    short offsetX;
    short offsetY;
    char unk4C[0xC];
    int width;
    int height;
    char unk60[0x1C];
    int timer;
    short *counter;
};

int HudTex_GetFrame(int texture, int frame);
void Hud_DrawFlatRect(int left, int top, int right, int bottom, unsigned long rgba, int mode);
void Hud_DrawFlatRectFixed(int left, int top, int right, int bottom, unsigned long rgba, int mode);
void Hud_DrawTexQuad(int frame, int x, int y, int width, int height, int alpha);
void Hud_DrawTexQuadF(int frame, int x, int y, int width, int height, int u, int v, int alpha);
int HudTex_Bind(int frame);
void Hud_DrawRotatedSprite16(float cx, float cy, float width, float height, float theta, int texW, int texH, unsigned long tex0);
void Hud_SetEntryValueById(int id, int value);
void HudStub(void);

typedef void (*HudFunction)(HudEntry *entry);

// Adds a HUD entry with its init, update and draw functions; returns its handle.
int RegisterHUDCallback(int type, int texture, HudFunction init, HudFunction update, HudFunction draw, void *value, int maximum);
// Keeps the entry on screen for the given frames; nonzero when it is no longer registered.
int Hud_SetEntryMinValueById(int handle, int frames);
int Hud_SetEntryIconById(int handle);
void HudEntry_InitCounterSlide(HudEntry *entry);

void Draw_PromptMsg(HudEntry *entry);

void BoltHud_Update(HudEntry *entry);
void Draw_BoltCountUI(HudEntry *entry);
// Shows a help prompt with the given text.
void GetHelpLen(char *text);

void Hud_GetTexIndex(HudEntry *entry);

void HudEntry_UpdateCounterWrap(HudEntry *entry);

void HudEntry_InitCounter(HudEntry *entry);

void HudEntry_RoundFixed(HudEntry *entry);

void Hud_DrawTexQuadUV_Fixed(HudEntry *entry);

void HudEntry_InitCounter32(HudEntry *entry);

void HudHeap_Reset(void);

void *HudHeap_Alloc(int size);

#endif
