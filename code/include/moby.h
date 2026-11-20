#ifndef MOBY_H
#define MOBY_H

// Quadword vector; the VU loads it with lq/sq, so it is 16-byte aligned.
struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));

struct Mtx4 {
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    Vec4 v3;
};

struct BSphere {
    float x;
    float y;
    float z;
    float rad;
};

struct MobyClass;
struct Manipulator;

// Bits of MobyInstance::modeBits.
enum MobyModeBit {
    NONE = 0,
    DISABLED = 1,
    NO_UPDATE = 2,
    NO_POST_UPDATE = 4,
    TRANSPARENT = 8,
    HAS_GLOW = 16,
    HAS_SPECIAL_VARS = 32,
    UNK_40 = 64,
    NO_DRAW = 128,
    LOCK_ROTATION = 256,
    DRAW_TRANSPARENT_WEIRD = 512,
    DRAW_SHADOW = 1024,
    DISABLE_Z_WRITE = 2048,
    CAN_BE_AUTO_TARGETED = 4096,
    HIDE_BACKFACES = 8192,
    CAN_BE_DAMAGED = 16384,
    MIRROR = 32768
};

// A moby (game object) instance, 0x100 bytes.
struct MobyInstance {
    BSphere bSphere;
    Vec4 pos;
    unsigned char state;
    signed char group;
    unsigned char mClass;
    signed char alpha;
    MobyClass *pClass;
    void *pChain;
    float scale;
    char updateDistance;
    char enabled;
    short drawDistance;
    unsigned short modeBits;
    unsigned short occlIndex;
    union {
        unsigned long long lights;
        struct {
            unsigned int color;
            unsigned int light;
        };
    };
    Vec4 rotation;
    char previousAnimationFrame;
    char animationFrame;
    unsigned char updateId;
    unsigned char animationId;
    float animationBlend;
    float unk58;
    float frameSpeed;
    void *pAnimationLayers;
    Manipulator *pManipulators;
    void *pPreviousAnimationData;
    void *pCurrentAnimationData;
    char unk70[4];
    void *pUpdate;
    void *pVar;
    char soundDesired;
    char soundChannel;
    char trigsCnt;
    char shadow;
    int colorManipulator;
    float zMin;
    float zMax;
    char unk8C[4];
    unsigned int glowRgba;
    unsigned short *collision;
    float *collisionMesh;
    int collQueryStamp;
    unsigned int collCount;
    signed char damage;
    char previousAnimationId;
    unsigned short oClass;
    int handle;
    unsigned int index;
    char levelFlagIdx;
    char unkB1;
    unsigned short uid;
    char unkB4[4];
    MobyInstance *unkB8;
    char setByGroup;
    char unkBD;
    char unkBE[2];
    Mtx4 transform;
};

void SetLevelFlag(int flag);

extern int StashedMobyClassDists[];

void InitMobyClassDists(void);

void StashMobyClassDists(void);

void RestoreMobyClassDists(void);

void MB_GetBonePos(MobyInstance *moby, int index, Vec4 *out);

#endif
