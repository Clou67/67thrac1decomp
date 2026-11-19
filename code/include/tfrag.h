#ifndef TFRAG_H
#define TFRAG_H

#include "moby.h"

// A tfrag (field names from the PS3 project, PS2 offsets). Positions are fixed point.
struct Tfrag {
    BSphere bSphere;
    char unk10[0x25];
    // Set when no point light is left on it.
    char dir_lights_upd;
    // Four 4-bit point light slots, 0xF is empty.
    unsigned short point_lights;
    char unk38[8];
};

extern Tfrag *Tfrags;
extern int TfragsCnt;

#endif
