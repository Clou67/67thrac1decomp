#ifndef FASTFUNC_H
#define FASTFUNC_H

// Stops in the debugger; used when a save is bigger than its buffer.
void FastTrap(void);
void FastMemCopy32(void *destination, void *source, int size);

#endif
