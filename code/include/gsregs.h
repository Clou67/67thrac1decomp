#ifndef GSREGS_H
#define GSREGS_H

// GS register addresses written through packets (A+D).
#define GS_REG_CLAMP_1 0x08
#define GS_REG_ALPHA_1 0x42
#define GS_REG_TEST_1 0x47

// CLAMP_1 wrap modes: repeat both axes, or clamp both.
#define GS_CLAMP_REPEAT 0
#define GS_CLAMP_CLAMP 5

#endif
