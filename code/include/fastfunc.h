#ifndef FASTFUNC_H
#define FASTFUNC_H

// Stops in the debugger; used when a save is bigger than its buffer.
void FastTrap(void);
int FastScaleRoundInt(int value);
int FastTweenColor(int from, int to, float fraction);
int FastFloatToInt(float value);
float FastIntToFloat(int value);
float FastAngleCosF(float angle);
// Counts a timer down to zero; returns nonzero once it has run out.
int FastDecTimer(int &timer);
float FastVec3Length(float *vec);
void FastMemCopy32(void *destination, void *source, int size);

#endif
