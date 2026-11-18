#ifndef MOBY_H
#define MOBY_H

#define MOBY_FLAG_HIDDEN 0x1

// Only the fields the freeze mode touches are known so far.
struct MobyInstance {
    char unk0[0x31];
    unsigned char visible;
    char unk32[2];
    unsigned short flags;
    char unk36[0x5E];
    int collision;
};

#endif
