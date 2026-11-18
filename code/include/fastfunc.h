#ifndef FASTFUNC_H
#define FASTFUNC_H

// Stops in the debugger; used when a save is bigger than its buffer.
void FastTrap(void);
int FastScaleRoundInt(int value);
// Counts a timer down to zero; returns nonzero once it has run out.
int FastDecTimer(int &timer);
float FastVec3Length(float *vec);
void FastMemCopy32(void *destination, void *source, int size);

#endif
