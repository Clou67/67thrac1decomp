#ifndef HUD_H
#define HUD_H

int HudTex_GetFrame(int texture, int frame);
void Hud_DrawFlatRect(int left, int top, int right, int bottom, unsigned long rgba, int mode);
void Hud_DrawFlatRectFixed(int left, int top, int right, int bottom, unsigned long rgba, int mode);
void Hud_DrawTexQuad(int frame, int x, int y, int width, int height, int alpha);
void Hud_DrawTexQuadF(int frame, int x, int y, int width, int height, int u, int v, int alpha);
int HudTex_Bind(int frame);
void Hud_DrawRotatedSprite16(float cx, float cy, float width, float height, float theta, int texW, int texH, unsigned long tex0);
void Hud_SetEntryValueById(int id, int value);
void HudStub(void);

#endif
