#ifndef PAD_H
#define PAD_H

// Only the button words are known so far (DL struct PAD, RC1 offsets).
struct PAD {
    char unk0[0x1A0];
    int bits;
    int bitsOn;
};

extern PAD padState;

void UpdatePad(void);

#define PAD_L2 0x0001
#define PAD_R2 0x0002
#define PAD_L1 0x0004
#define PAD_R1 0x0008
#define PAD_TRIANGLE 0x0010
#define PAD_CIRCLE 0x0020
#define PAD_CROSS 0x0040
#define PAD_START 0x0800
#define PAD_UP 0x1000
#define PAD_RIGHT 0x2000
#define PAD_DOWN 0x4000
#define PAD_LEFT 0x8000
#define PAD_DPAD (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)

#endif
