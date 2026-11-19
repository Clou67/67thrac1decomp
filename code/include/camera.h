#ifndef CAMERA_H
#define CAMERA_H

#include "moby.h"

// Camera rotation as the PS3 project names it; radius holds the yaw.
struct PolarSm {
    float azimuth;
    float elevation;
    float radius;
};

// The game camera (field names from the PS3 project; only the fields known so far).
struct GAMECAMERA {
    Mtx4 mtx0;
    Mtx4 matrix;
    Mtx4 mtx2;
    Mtx4 mtx3;
    Mtx4 mtx4;
    float posX;
    float posY;
    float posZ;
    float posW;
    PolarSm rot;
    float rotW;
    char unk160[0x23C];
};

extern GAMECAMERA GameCamera;

#endif
