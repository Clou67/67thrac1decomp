#ifndef DRAW_H
#define DRAW_H

void DrawRoundedRect(int top, int bottom, int left, int right, int rgba);
void DrawTextShadow(int top, int bot, int left, int right, int alpha);
void DrawSprite(int sc_x, int sc_y, int sc_w, int sc_h, int tx_u, int tx_v, int tx_w, int tx_h, unsigned long rgba, unsigned long tex0);

// Starts and ends a VU1 frame packet chain.
void FlipAndExploreTimersVU1(int arg);
void FinalizeVU1FramePacketChain(void);

// Frame counter of the GS display.
extern int gsFrame;
// Nonzero when the console is running in PAL mode.
extern int videoModePal;

void FadeToBlack(int frames);

void InitViewContext(void);
void UpdateViewContext(void);

#endif
