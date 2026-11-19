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

void STUB_RET_2525f0(void)
{
}

int CreatePointLight3(Vec4 *pos, float radius, float intensity, int rgb)
{
    PointLight *light;
    PL_Data *data;
    int index;

    if (PerfLoad > POINT_LIGHT_MAX_LOAD) {
        return -1;
    }

    for (index = 0; index < MAX_POINT_LIGHTS; index++) {
        if (PointLightData[index].state == POINT_LIGHT_FREE) {
            break;
        }
    }

    if (index == MAX_POINT_LIGHTS) {
        return -1;
    }

    light = &PointLights[index];
    data = &PointLightData[index];

    CopyVec4(&light->pos, pos);
    light->pos.w = radius;
    light->color.x = FastIntToFloat(rgb & 0xFF) * COLOR_CHANNEL_SCALE;
    light->color.y = FastIntToFloat((rgb >> 8) & 0xFF) * COLOR_CHANNEL_SCALE;
    light->color.z = FastIntToFloat((rgb >> 16) & 0xFF) * COLOR_CHANNEL_SCALE;
    light->color.w = intensity;

    FastMemSetZero(data, sizeof(PL_Data));
    data->state = POINT_LIGHT_CREATED;
    data->list = PointLightLists[index];

    return index;
}

int CreatePointLight2(Vec4 *pos, float radius, float intensity, float red, float green, float blue)
{
    PointLight *light;
    PL_Data *data;
    int index;

    if (PerfLoad > POINT_LIGHT_MAX_LOAD) {
        return -1;
    }

    for (index = 0; index < MAX_POINT_LIGHTS; index++) {
        if (PointLightData[index].state == POINT_LIGHT_FREE) {
            break;
        }
    }

    if (index == MAX_POINT_LIGHTS) {
        return -1;
    }

    light = &PointLights[index];
    data = &PointLightData[index];

    CopyVec4(&light->pos, pos);
    light->pos.w = radius;
    light->color.x = red;
    light->color.y = green;
    light->color.z = blue;
    light->color.w = intensity;

    FastMemSetZero(data, sizeof(PL_Data));
    data->state = POINT_LIGHT_CREATED;
    data->list = PointLightLists[index];

    return index;
}

void DeletePointLight(int light)
{
    DetachPointLight(light);

    FastMemSetZero(&PointLights[light], sizeof(PointLight));
    FastMemSetZero(&PointLightData[light], sizeof(PL_Data));
}

void UpdatePointLights(void)
{
    float yaw;
    int index;

    // Grey light from above that turns with the camera.
    DirectionalLights[CAMERA_LIGHT].color1.x = 0.8f;
    DirectionalLights[CAMERA_LIGHT].color1.y = 0.8f;
    DirectionalLights[CAMERA_LIGHT].color1.z = 0.8f;
    DirectionalLights[CAMERA_LIGHT].color1.w = -0.3f;

    yaw = FastAddRots(GameCamera.rot.z, -0.8f);
    DirectionalLights[CAMERA_LIGHT].direction1.x = FastAngleSinF(yaw) * 0.866f;
    DirectionalLights[CAMERA_LIGHT].direction1.y = FastAngleCosF(yaw) * 0.866f;
    DirectionalLights[CAMERA_LIGHT].direction1.z = -0.5f;
    DirectionalLights[CAMERA_LIGHT].direction1.w = 0.0f;

    // Rebuild the lists of lights that moved more than the margin since they were built.
    for (index = 0; index < MAX_POINT_LIGHTS; index++) {
        PointLight *light = &PointLights[index];
        PL_Data *data = &PointLightData[index];

        if (data->state == POINT_LIGHT_FREE) {
            continue;
        }

        if (FastVec3Dist(&light->pos, &data->update_pos) > POINT_LIGHT_MARGIN) {
            CopyVec4(&data->update_pos, &light->pos);
            if (data->state == POINT_LIGHT_CREATED) {
                CreatePointLight(index);
                data->state = POINT_LIGHT_ATTACHED;
            } else if (data->state == POINT_LIGHT_ATTACHED) {
                RefreshPointLight(index);
            }
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", CreatePointLight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", RefreshPointLight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/lights", DetachPointLight);
