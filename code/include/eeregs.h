#ifndef EEREGS_H
#define EEREGS_H

// EE hardware registers (names from Sony eeregs.h).
#define D0_CHCR ((volatile unsigned int *)0x10008000)
#define D0_QWC ((volatile unsigned int *)0x10008020)
#define D0_TADR ((volatile unsigned int *)0x10008030)
#define D1_CHCR ((volatile unsigned int *)0x10009000)
#define D1_TADR ((volatile unsigned int *)0x10009030)
#define D_STAT ((volatile unsigned int *)0x1000E010)

// D_CHCR: channel busy (start) bit.
#define D_CHCR_STR 0x100

#endif
