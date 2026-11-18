#ifndef DRAW_H
#define DRAW_H

// Starts and ends a VU1 frame packet chain.
void FlipAndExploreTimersVU1(int arg);
void FinalizeVU1FramePacketChain(void);

// Frame counter of the GS display.
extern int gsFrame;
// Nonzero when the console is running in PAL mode.
extern int videoModePal;

#endif
