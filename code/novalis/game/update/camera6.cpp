#include "common.h"
#include "vtbl.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", FUN_003176d0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", FUN_00317778);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", FUN_00317808);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", FUN_003178d8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", FUN_00317aa0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", FUN_00317d88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", FUN_00317e70);

int InitCamera_6(UpdateCam *camera)
{
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera6", ActivateCamera_6);

void Camera6_UpdateOrbit(UpdateCam *camera);

void UpdateCamera_6(UpdateCam *camera)
{
    Camera6_UpdateOrbit(camera);
}

void ExitCamera_6(UpdateCam *camera)
{
}
