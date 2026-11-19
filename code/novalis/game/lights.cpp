#include "common.h"
#include "lights.h"
#include "camera.h"
#include "fastfunc.h"
#include "framebuf.h"
#include "mathinline.h"
#include "vuchain.h"

// Each light lists the ties, tfrags and shrubs its sphere (radius + POINT_LIGHT_MARGIN)
// touches, and writes its index into their point_lights masks: four 4-bit slots,
// 0xF is empty, kept packed from the low end.
#define POINT_LIGHT_MARGIN 8.0f
#define POINT_LIGHT_MAX_LOAD 0.8f
#define POINT_LIGHT_SLOTS_EMPTY 0xFFFF

// Tfrag positions are fixed point, 1024 units to a world unit.
#define TFRAG_POSITION_SCALE 1024.0f

// Packed colours are 0xBBGGRR with 0x80 meaning 1.0.
#define COLOR_CHANNEL_SCALE (1.0f / 128.0f)

// Directional light slot rebuilt every frame around the camera.
#define CAMERA_LIGHT 13

enum point_light_state {
    POINT_LIGHT_FREE,
    POINT_LIGHT_CREATED,
    POINT_LIGHT_ATTACHED
};

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", STUB_RET_2525f0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", CreatePointLight3);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", CreatePointLight2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", DeletePointLight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", UpdatePointLights);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", CreatePointLight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", RefreshPointLight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", DetachPointLight);
