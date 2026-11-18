#ifndef EEKERNEL_H
#define EEKERNEL_H

// From Sony eekernel.h: interrupt handlers return through sync.l; ei.
#define ExitHandler() asm volatile("sync.l; ei")

#endif
