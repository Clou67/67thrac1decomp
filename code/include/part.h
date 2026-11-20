#ifndef PART_H
#define PART_H

#include "moby.h"

struct PartLineMotion {
    Vec4 origin;
    Vec4 velocity;
};

struct PartTimedFade {
    Vec4 velocity;
    int timer;
    int duration;
    int alpha;
};

struct PartSpinMotion {
    Vec4 velocity;
    union {
        char rotationStep;
        int relativeToHero;
    };
};

struct PartScaleFade {
    float startScale;
    float endScale;
    int startColor;
    int endColor;
    float rate;
};

struct PartFadingMotion {
    Vec4 velocity;
    float scaleStep;
};

struct PartRotationMotion {
    char unk_00[0x18];
    char rotationStep;
};

struct PartInstance {
    char i_class;
    char type;
    char tex;
    char gs_alpha;
    int rgba;
    char rot;
    char draw_dist;
    short timer;
    union {
        float scale;
        int rgbaScale;
    };
    Vec4 pos;
    union {
        int update[8];
        PartLineMotion motion20;
        PartTimedFade timedFade;
        PartSpinMotion spinMotion;
        PartScaleFade scaleFade;
        PartFadingMotion fadingMotion;
        PartRotationMotion rotationMotion;
    };
};

void UpdatePart_018(PartInstance *part);

void UpdatePart_034(PartInstance *part);

void UpdatePart_042(PartInstance *part);

void UpdatePart_064(PartInstance *part);

void UpdatePart_020(PartInstance *part);

void UpdatePart_057(PartInstance *part);

#endif
