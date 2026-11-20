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

struct MobyCollPrims {
    char unk00[8];
    int count;
};

struct MobySeqFrame {
    char unk_00[4];
    short time;
};

// The frame pointer table follows the 0x1C-byte RaC1 sequence header.
struct MobySeq {
    BSphere bSphere;              // 0x00
    unsigned char frameCount;    // 0x10
    signed char sound;           // 0x11
    unsigned char triggerCount;  // 0x12
    unsigned char unk_13;
    short *triggers;              // 0x14
    unsigned int unk_18;
    MobySeqFrame *frames[1];      // 0x1C, frameCount entries
};

struct MobyPacket;
struct MobyGifUsage;
struct SoundDef;

// The animation pointer table follows the 0x48-byte RaC1 class header.
struct MobyInstance;
typedef int (*MobyClassCallback)(MobyInstance *moby);

struct MobyClassCallbacks {
    int unk_00;
    MobyClassCallback callback04;
    MobyClassCallback callback08;
    MobyClassCallback callback0C;
};

struct MobyClass {
    MobyPacket *packets;                // 0x00
    unsigned char packetCount0;        // 0x04
    unsigned char packetCount1;        // 0x05
    unsigned char metalCount;          // 0x06
    unsigned char unk_07;
    unsigned char jointCount;          // 0x08
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char sequenceCount;       // 0x0C
    unsigned char soundCount;          // 0x0D
    unsigned char lodTransition;       // 0x0E
    unsigned char shadowCount;         // 0x0F
    MobyCollPrims *collision;           // 0x10
    void *skeleton;                     // 0x14
    Vec4 *commonTranslations;           // 0x18
    void *animationJoints;              // 0x1C
    MobyGifUsage *gifUsage;              // 0x20
    float scale;                        // 0x24
    SoundDef *soundDefs;                // 0x28
    // The loader saves mipDistance before the runtime slot can hold callbacks.
    union {                             // 0x2C
        unsigned int mipDistance;
        MobyClassCallbacks *callbacks;
    };
    BSphere bSphere;                    // 0x30
    unsigned int glowRgba;              // 0x40
    unsigned short modeBits;            // 0x44
    short type;                         // 0x46
    MobySeq *animations[1];              // 0x48, sequenceCount entries
};
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
    union {
        unsigned short *collision;
        MobyCollPrims *pCollPrims;
    };
    float *collisionMesh;
    int collQueryStamp;
    unsigned int collCount;
    signed char damage;
    unsigned char previousAnimationId;
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

enum { ANIM_CACHE_COUNT = 16 };
extern MobyInstance *AnimationCacheRegistry[ANIM_CACHE_COUNT];

void SetLevelFlag(int flag);

extern int StashedMobyClassDists[];

void InitMobyClassDists(void);

void StashMobyClassDists(void);

void RestoreMobyClassDists(void);

void MB_GetBonePos(MobyInstance *moby, int index, Vec4 *out);

void MB_GetBoneTransformation(MobyInstance *moby, int index, Mtx4 *out);

int MB_FindNearestAnimTrigger(MobySeq *sequence, float time);

void MB_GetJointsWorldMtx(MobyInstance *moby, int count, int *indices, Mtx4 *joints);

int M849_CallClassCallback04(MobyInstance *moby);

int M849_CallClassCallback0C(MobyInstance *moby);

int AnimCache_Register(MobyInstance *moby);

void GetMobyJointsWorldPos(MobyInstance *moby, int count, int *joints, Vec4 *out);

#endif
