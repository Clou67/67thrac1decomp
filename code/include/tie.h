#ifndef TIE_H
#define TIE_H

#include "moby.h"

// A tie instance (field names from the PS3 project, PS2 offsets).
struct TieInstance {
    BSphere bSphere;
    char unk10[0xB];
    // Set when no point light is left on it.
    char dir_lights_upd;
    char unk1C[2];
    // Four 4-bit point light slots, 0xF is empty.
    unsigned short point_lights;
};

extern TieInstance *TieInstances;
extern TieInstance *TieInstanceEnd;

#endif
