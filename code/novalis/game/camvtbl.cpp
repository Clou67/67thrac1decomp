#include "common.h"
#include "vtbl.h"

// Camera behaviours used in this level. Ends with id -1.
const CameraUpdateEntry cameraupdate_vtbl[] = {
    { 0, InitCamera_0, ActivateCamera_0, UpdateCamera_0, ExitCamera_0 },
    { 3, InitCamera_3, ActivateCamera_3, UpdateCamera_3, ExitCamera_3 },
    { 4, InitCamera_4, ActivateCamera_4, UpdateCamera_4, ExitCamera_4 },
    { 5, InitCamera_5, ActivateCamera_5, UpdateCamera_5, ExitCamera_5 },
    { 6, InitCamera_6, ActivateCamera_6, UpdateCamera_6, ExitCamera_6 },
    { 7, InitCamera_7, ActivateCamera_7, UpdateCamera_7, ExitCamera_7 },
    { 17, InitCamera_17, ActivateCamera_17, UpdateCamera_17, ExitCamera_17 },
    { -1, 0, 0, 0, 0 },
};
