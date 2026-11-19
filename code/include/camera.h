#ifndef CAMERA_H
#define CAMERA_H

#include "moby.h"

// The game camera (only the fields known so far).
struct GameCameraState {
    Mtx4 matrices[5];
    Vec4 pos;
    // Camera orientation; z is the yaw.
    Vec4 rot;
    char unk160[0x23C];
};

extern GameCameraState GameCamera;

#endif
