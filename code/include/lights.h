#ifndef LIGHTS_H
#define LIGHTS_H

#include "moby.h"
#include "shrub.h"
#include "tfrag.h"
#include "tie.h"

#define MAX_POINT_LIGHTS 8
#define POINT_LIGHT_LIST_LENGTH 512

// One point light: its colour (w is the backlight) and position (w is the radius).
struct PointLight {
    Vec4 color;
    Vec4 pos;
};

// What a point light is attached to: ranges into list of tie, tfrag and shrub indices.
struct PL_Data {
    short tie_offset;
    short tie_count;
    short shrub_offset;
    short shrub_count;
    short tfrag_offset;
    short tfrag_count;
    short *list;
    int state;
    int pad[3];
    // Light position the lists were last built at.
    Vec4 update_pos;
};

struct DirectionalLight {
    Vec4 color1;
    Vec4 direction1;
    Vec4 color2;
    Vec4 direction2;
};

extern PointLight PointLights[MAX_POINT_LIGHTS];
extern PL_Data PointLightData[MAX_POINT_LIGHTS];
extern short PointLightLists[MAX_POINT_LIGHTS][POINT_LIGHT_LIST_LENGTH];
extern DirectionalLight DirectionalLights[16];

// Fraction of the frame budget in use; no new point lights are made above 0.8.
extern float PerfLoad;

void STUB_RET_2525f0(void);
// Packed colour 0xBBGGRR, 0x80 = 1.0.
int CreatePointLightRGB(Vec4 &pos, float radius, float backlight, int rgb);
int CreatePointLight(Vec4 &pos, float radius, float backlight, float red, float green, float blue);
void DeletePointLight(int light);
void UpdatePointLights(void);
// Builds the light's lists of the ties, tfrags and shrubs it touches.
void AttachPointLight(int light);
void RefreshPointLight(int light);
void DetachPointLight(int light);

#endif
