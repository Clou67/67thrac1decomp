#ifndef LIGHTS_H
#define LIGHTS_H

#include "moby.h"

#define MAX_POINT_LIGHTS 8
#define POINT_LIGHT_LIST_LENGTH 512

// One point light: its colour (w is the intensity) and position (w is the radius).
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

// Instances a point light can attach to. point_lights holds four 4-bit light slots
// (0xF is empty); dir_lights_upd is set when no point light is left on it.
struct TieInstance {
    BSphere bsphere;
    char unk10[0xB];
    char dir_lights_upd;
    char unk1C[2];
    unsigned short point_lights;
};

struct ShrubInstance {
    BSphere bsphere;
    float draw_dist;
    char pad[2];
    char flags;
    char bboard_dist;
    short index;
    char s_class;
    char dir_lights_upd;
    unsigned short dir_lights;
    unsigned short point_lights;
};

struct Tfrag {
    BSphere bsphere;
    char unk10[0x25];
    char dir_lights_upd;
    unsigned short point_lights;
    char unk38[8];
};

extern PointLight PointLights[MAX_POINT_LIGHTS];
extern PL_Data PointLightData[MAX_POINT_LIGHTS];
extern short PointLightLists[MAX_POINT_LIGHTS][POINT_LIGHT_LIST_LENGTH];
extern DirectionalLight DirectionalLights[16];

extern TieInstance *TieInstances;
extern TieInstance *TieInstanceEnd;
extern ShrubInstance *ShrubInstances;
extern ShrubInstance *ShrubInstanceEnd;
extern Tfrag *Tfrags;
extern int TfragsCnt;

// Fraction of the frame budget in use; no new point lights are made above 0.8.
extern float PerfLoad;

void STUB_RET_2525f0(void);
int CreatePointLight3(Vec4 *pos, float radius, float intensity, int rgb);
int CreatePointLight2(Vec4 *pos, float radius, float intensity, float red, float green, float blue);
void DeletePointLight(int light);
void UpdatePointLights(void);
void CreatePointLight(int light);
void RefreshPointLight(int light);
void DetachPointLight(int light);

#endif
