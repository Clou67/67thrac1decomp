#ifndef SHRUB_H
#define SHRUB_H

#include "moby.h"

// A shrub instance (DL's PS2 layout).
struct ShrubInstance {
    BSphere bSphere;
    float draw_dist;
    char pad[2];
    char flags;
    char bboard_dist;
    short index;
    char s_class;
    // Set when no point light is left on it.
    char dir_lights_upd;
    unsigned short dir_lights;
    // Four 4-bit point light slots, 0xF is empty.
    unsigned short point_lights;
};

extern ShrubInstance *ShrubInstances;
extern ShrubInstance *ShrubInstanceEnd;

#endif
